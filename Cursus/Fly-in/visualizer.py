import tkinter as tk
from config import Configure
from graph import Hub, Zone
from colors import Color
from math import sqrt, atan


class GraphCanvas(tk.Canvas):
    def __init__(self, master, **kwargs):
        super().__init__(master, **kwargs)
        self._origin = {"x": 0, "y": 0}
        self._sc_up = 1.1
        self._sc_down = 0.9
        self._cscale = 1
        self._font = Configure.font
        self.bind("<ButtonPress-1>", self._set_origin)
        self.bind("<B1-Motion>", self._pan)
        self.bind("<Button-4>", self._scale)
        self.bind("<Button-5>", self._scale)

    def _set_origin(self, event):
        self._origin["x"] = event.x
        self._origin["y"] = event.y

    def _pan(self, event):
        self.move(
            "all", event.x - self._origin["x"], event.y - self._origin["y"]
        )
        self._origin["x"] = event.x
        self._origin["y"] = event.y

    def _scale(self, event):
        if event.num == 4:
            self._cscale *= self._sc_up
            self.scale("all", event.x, event.y, self._sc_up, self._sc_up)
        elif event.num == 5:
            self._cscale *= self._sc_down
            self.scale("all", event.x, event.y, self._sc_down, self._sc_down)
        self._font = (self._font[0], int(Configure.font[1] * self._cscale))
        self.itemconfig("text", font=self._font)

    def _create_custom_label(
        self,
        x_c: float,
        y_c: float,
        text: str,
        width: float,
        height: float,
        fill: str = Configure.fill_color,
        radius: tuple[int, int, int, int] = (0, 0, 0, 0),
    ):
        h_w = 0.5 * width
        h_h = 0.5 * height
        r1, r2, r3, r4 = radius

        points = [
            x_c - h_w,
            y_c - h_h + r1,
            x_c - h_w,
            y_c - h_h,
            x_c - h_w + r1,
            y_c - h_h,
            x_c + h_w - r2,
            y_c - h_h,
            x_c + h_w,
            y_c - h_h,
            x_c + h_w,
            y_c - h_h + r2,
            x_c + h_w,
            y_c + h_h - r3,
            x_c + h_w,
            y_c + h_h,
            x_c + h_w - r3,
            y_c + h_h,
            x_c - h_w + r4,
            y_c + h_h,
            x_c - h_w,
            y_c + h_h,
            x_c - h_w,
            y_c + h_h - r4,
        ]

        canvas.create_polygon(
            *points,
            fill=fill,
            outline=Configure.border_color,
            width=Configure.border_width,
            smooth=True,
        )

        if text:
            canvas.create_text(
                x_c,
                y_c,
                text=text,
                fill=Configure.text_color,
                font=self._font,
                tags="text",
            )

    def create_hub(self, hub: Hub):
        if hub.color:
            _hub_color = Color[hub.color.upper()].hex
        else:
            _hub_color = Configure.fill_color

        match hub.zone:
            case Zone.NORMAL:
                _name = "N: " + hub.name
            case Zone.PRIORITY:
                _name = "P: " + hub.name
            case Zone.RESTRICTED:
                _name = "R: " + hub.name
            case Zone.BLOCKED:
                _name = "B: " + hub.name

        temp = self.create_text(-1000, -1000, text=_name, font=self._font)
        self.update_idletasks()
        bbox = self.bbox(temp)
        self.delete(temp)

        if bbox is not None:
            width = bbox[2] - bbox[0] + 1.1 * self._font[1]
            height = bbox[3] - bbox[1] + 1.1 * self._font[1]
        else:
            width = 4 * self._font[1]
            height = 2 * self._font[1]

        _br = Configure.border_radius
        _r1 = (_br, _br, 0, 0)
        _r2 = (0, 0, _br, _br)

        self._create_custom_label(
            hub.x,
            hub.y - 0.5 * height,
            text=_name,
            width=width,
            height=height,
            fill=_hub_color,
            radius=_r1,
        )

        self._create_custom_label(
            hub.x,
            hub.y + 0.5 * height,
            text=f"{len(hub.drones)} / {hub.max_drones}",
            width=width,
            height=height,
            fill="",
            radius=_r2,
        )

    def create_edge(self, _from: Hub, _to: Hub, cap: int = 1, arrow_size=1.8):
        d1, d2, d3 = tuple(map(lambda x: arrow_size * x, (8, 10, 3)))
        x0, y0 = _from.x, _from.y
        x1, y1 = _to.x, _to.y
        dx = x1 - x0
        dy = y1 - y0
        dist = sqrt(dx**2 + dy**2)
        if dist == 0:
            return
        start_x = x0 + (dx / dist)
        start_y = y0 + (dy / dist)
        end_x = x1 - (dx / dist)
        end_y = y1 - (dy / dist)
        self.create_line(
            start_x,
            start_y,
            end_x,
            end_y,
            arrow="last",
            fill=Configure.edge_color,
            width=2,
            arrowshape=(d1, d2, d3),
        )
        self.create_oval(
            x0 + (dx / dist) * dist * 0.5 - self._font[1],
            y0 + (dy / dist) * dist * 0.5 - self._font[1],
            x0 + (dx / dist) * dist * 0.5 + self._font[1],
            y0 + (dy / dist) * dist * 0.5 + self._font[1],
            fill=self["background"],
            width=0,
        )
        self.create_text(
            x0 + (dx / dist) * dist * 0.5,
            y0 + (dy / dist) * dist * 0.5,
            text=str(cap),
            font=self._font,
            angle=-atan(dy / dx) * 57.295779513,
            tags="text",
        )

    def create_graph(
        nodes: list[tuple[int, int]],
    ) -> list[tuple[float, float]]:
        if not nodes:
            return []

        # Initialize to first node
        x0_bbox = x1_bbox = nodes[0][0]
        y0_bbox = y1_bbox = nodes[0][1]

        for x, y in nodes:
            x0_bbox = min(x0_bbox, x)
            y0_bbox = min(y0_bbox, y)
            x1_bbox = max(x1_bbox, x)
            y1_bbox = max(y1_bbox, y)

        # Handle single point or line cases
        width_bbox = x1_bbox - x0_bbox
        height_bbox = y1_bbox - y0_bbox

        if width_bbox == 0 and height_bbox == 0:
            scale = 1
        elif width_bbox == 0:
            scale = Configure.height / height_bbox * 0.9
        elif height_bbox == 0:
            scale = Configure.width / width_bbox * 0.9
        else:
            scale = (
                min(
                    Configure.width / width_bbox,
                    Configure.height / height_bbox,
                )
                * 0.9
            )

        # Center of nodes
        x_c = (x0_bbox + x1_bbox) / 2
        y_c = (y0_bbox + y1_bbox) / 2

        # Scale, center, and translate to canvas center
        return [
            (
                (x - x_c) * scale + Configure.width / 2,
                (y - y_c) * scale + Configure.height / 2,
            )
            for x, y in nodes
        ]

    # for node in center(test_graph):
    #     create_drone(*node)


root = tk.Tk()
root.geometry("1000x1000")


canvas = GraphCanvas(root)
canvas.pack(expand=True, fill="both")


test = Hub("test_hub", 300, 300, color="green")
test2 = Hub("test_hub2", 150, 150, color="yellow")
canvas.create_hub(test)
canvas.create_hub(test2)
canvas.create_edge(test, test2)


root.mainloop()
