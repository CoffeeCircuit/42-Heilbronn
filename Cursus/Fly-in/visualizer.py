import tkinter as tk
from math import sqrt


# from PIL import Image, ImageTk
# bg_img = Image.open("42.png")  # Use your image path
# bg_photo = ImageTk.PhotoImage(bg_img)
# canvas.create_image(400, 400, image=bg_photo, anchor="center")


class Render(tk.Tk):
    class GraphCanvas(tk.Canvas):
        def __init__(self, master, **kwargs):
            super().__init__(master, **kwargs)
            self.scale_factor = 1.0
            self._drag_data = {"x": 0, "y": 0}
            self.text_items = {}
            self.bind("<ButtonPress-1>", self.start_pan)
            self.bind("<B1-Motion>", self.do_pan)
            self.bind("<MouseWheel>", self.do_zoom)
            self.bind("<Button-4>", self.do_zoom)
            self.bind("<Button-5>", self.do_zoom)

        def create_text_scaled(self, *args, font=None, **kwargs):
            # font: tuple (font_name, base_size, *options)
            item = self.create_text(*args, font=font, **kwargs)
            if font is not None:
                # Store base font info for scaling
                self.text_items[item] = (
                    font[0],
                    font[1],
                    font[2:] if len(font) > 2 else (),
                )
            return item

        def start_pan(self, event):
            self._drag_data["x"] = event.x
            self._drag_data["y"] = event.y

        def do_pan(self, event):
            dx = event.x - self._drag_data["x"]
            dy = event.y - self._drag_data["y"]
            self.move("all", dx, dy)
            self._drag_data["x"] = event.x
            self._drag_data["y"] = event.y

        def do_zoom(self, event):
            # Cross-platform zoom direction
            factor = None
            if hasattr(event, "delta") and event.delta != 0:
                factor = 1.1 if event.delta > 0 else 0.9
            elif hasattr(event, "num"):
                if event.num == 4:
                    factor = 1.1
                elif event.num == 5:
                    factor = 0.9
            if factor is None:
                return
            # Clamp scale factor to avoid disappearing
            new_scale = self.scale_factor * factor
            if 0.2 < new_scale < 5:
                self.scale("all", event.x, event.y, factor, factor)
                self.scale_factor = new_scale
                self._rescale_texts()

        def _rescale_texts(self):
            for item, (
                font_name,
                base_size,
                font_opts,
            ) in self.text_items.items():
                new_size = max(1, int(base_size * self.scale_factor))
                new_font = (font_name, new_size) + tuple(font_opts)
                self.itemconfig(item, font=new_font)

        def animate_node(canvas, node_id, dx, dy, steps=50, delay=10):
            def step(count):
                if count < steps:
                    canvas.move(node_id, dx / steps, dy / steps)
                    canvas.after(delay, step, count + 1)

            step(0)

        def create_edge(n0, n1, directional=False, arrow_size=1.8):
            d1, d2, d3 = tuple(map(lambda x: arrow_size * x, (8, 10, 3)))
            x0, y0, r0 = n0
            x1, y1, r1 = n1
            dx = x1 - x0
            dy = y1 - y0
            dist = sqrt(dx**2 + dy**2)
            if dist == 0:
                return
            start_x = x0 + (dx / dist) * (r0 / 2)
            start_y = y0 + (dy / dist) * (r0 / 2)
            end_x = x1 - (dx / dist) * (r1 / 2)
            end_y = y1 - (dy / dist) * (r1 / 2)
            canvas.create_line(
                start_x,
                start_y,
                end_x,
                end_y,
                arrow="last" if directional else "both",
                fill="#b4befe",
                width=2,
                arrowshape=(d1, d2, d3),
            )

        def create_custom_label(
            canvas: tk.Canvas,
            x_c: int,
            y_c: int,
            text: str,
            width: float = 0,
            height: float = 0,
            radius: tuple[int, int, int, int] = (0, 0, 0, 0),
            text_color: str = "blue",
            fill_color: str = "",
            border_color: str = "red",
            border_width: int = 1,
            font: tuple[str, int] = ("System", 11),
        ):
            if text:
                lbl_string = canvas.create_text(
                    -1000, -1000, text=text, font=font
                )
                canvas.update_idletasks()
                bbox = canvas.bbox(lbl_string)
                canvas.delete(lbl_string)
                if bbox is not None:
                    width = max(width, bbox[2] - bbox[0] + 1.1 * font[1])
                    height = max(height, bbox[3] - bbox[1] + 1.1 * font[1])
                else:
                    # Fallback to default width/height if bbox is None
                    width = max(width, 4 * font[1])
                    height = max(height, 2 * font[1])

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
                fill=fill_color,
                outline=border_color,
                width=border_width,
                smooth=True,
            )
            if text:
                canvas.create_text(
                    x_c, y_c, text=text, fill=text_color, font=font
                )

        def draw_hub(canvas: tk.Canvas, hub: Hub):
            color = hub.color if hub.color else "yellow"
            match hub.zone:
                case ZoneType.zone_normal:
                    name = "N: " + hub.name
                case ZoneType.zone_priority:
                    name = "P: " + hub.name
                case ZoneType.zone_restricted:
                    name = "R: " + hub.name
                case ZoneType.zone_blocked:
                    name = "B: " + hub.name
            hub_flow = f"{len(hub.drones)} / {hub.max_drones}"
            lbl_width = max(map(len, (hub.name, hub_flow))) * 0.9 * 11
            create_custom_label(
                canvas,
                hub.x,
                hub.y - 15,
                text=name,
                radius=(20, 20, 0, 0),
                fill_color=color,
                width=lbl_width,
            )
            create_custom_label(
                canvas,
                hub.x,
                hub.y + 15,
                text=hub_flow,
                radius=(0, 0, 20, 20),
                width=lbl_width,
            )
