import tkinter as tk
from typing import Any
from config import Configure
from graph import Hub
from colors import Color
from math import sqrt, atan2


def get_complementary_color(hex_color: str) -> str:
    """Calculate complementary color for contrast"""
    hex_color = hex_color.lstrip("#")

    r = int(hex_color[0:2], 16)
    g = int(hex_color[2:4], 16)
    b = int(hex_color[4:6], 16)

    luminance = (0.299 * r + 0.587 * g + 0.114 * b) / 255

    if luminance < 0.5:
        return "#FFFFFF"
    else:
        return "#000000"


class GraphCanvas(tk.Canvas):
    def __init__(self, master: tk.Misc, **kwargs: Any) -> None:
        super().__init__(master, **kwargs)
        self._origin = {"x": 0, "y": 0}
        self._sc_up = 1.1
        self._sc_down = 0.9
        self._cscale: float = 1.0
        self._font: tuple[str, int] = Configure.font
        self.bind("<ButtonPress-1>", self._set_origin)
        self.bind("<B1-Motion>", self._pan)
        self.bind("<Button-4>", self._scale)
        self.bind("<Button-5>", self._scale)

        self.node_positions: dict[Hub, tuple[float, float]] = {}
        self.hub_items: dict[Hub, int] = {}
        self.drone_items: dict[int, tuple[int, int]] = {}
        self.edge_items: list[int] = []
        self.animation_queue: list[dict[int, tuple[Hub, Hub]]] = []
        self.current_turn = 0
        self.is_animating = False
        self.is_paused = False
        self.auto_play = False
        self.initial_positions: dict[int, Hub] = {}
        self.tooltip: tk.Toplevel | None = None

    def _set_origin(self, event: tk.Event) -> None:
        self._origin["x"] = event.x
        self._origin["y"] = event.y

    def _pan(self, event: tk.Event) -> None:
        self.move(
            "all", event.x - self._origin["x"], event.y - self._origin["y"]
        )
        self._origin["x"] = event.x
        self._origin["y"] = event.y

    def _scale(self, event: tk.Event) -> None:
        if event.num == 4:
            self._cscale *= self._sc_up
            self.scale("all", event.x, event.y, self._sc_up, self._sc_up)
        elif event.num == 5:
            self._cscale *= self._sc_down
            self.scale("all", event.x, event.y, self._sc_down, self._sc_down)
        else:
            return

        new_font_size: int = int(float(Configure.font[1]) * self._cscale)
        self._font = (self._font[0], new_font_size)
        self.itemconfig("text", font=self._font)

        base_arrow_size = 1.5 * self._cscale
        d1, d2, d3 = tuple(map(lambda x: base_arrow_size * x, (8, 10, 3)))
        for edge_id in self.edge_items:
            self.itemconfig(
                edge_id, arrowshape=(d1, d2, d3), width=2 * self._cscale
            )

    def _show_tooltip(self, event: tk.Event, hub: Hub) -> None:
        """Show tooltip with hub information"""
        self._hide_tooltip()

        self.tooltip = tk.Toplevel(self)
        self.tooltip.wm_overrideredirect(True)
        self.tooltip.wm_geometry(f"+{event.x_root + 10}+{event.y_root + 10}")

        label = tk.Label(
            self.tooltip,
            text=f"Type: {hub.type}\nName: {hub.name}\nZone: {hub.zone}",
            background="#ffffe0",
            relief="solid",
            borderwidth=1,
            padx=5,
            pady=3,
            font=("Arial", 10),
        )
        label.pack()

    def _hide_tooltip(self) -> None:
        """Hide the tooltip"""
        if self.tooltip:
            self.tooltip.destroy()
            self.tooltip = None

    def create_vertex(
        self, hub: Hub, original_hub: Hub | None = None
    ) -> int | None:
        r: float = Configure.text_padding * self._font[1]

        if str(hub.color).upper() == "RAINBOW":
            rainbow_colors = [
                "#FF0000",
                "#FFA500",
                "#FFFF00",
                "#00FF00",
                "#0000FF",
                "#4B0082",
                "#8B00FF",
            ]
            num_rings = len(rainbow_colors)
            oval_items = []

            for i, color in enumerate(rainbow_colors):
                ring_r = r * (1 - i / num_rings)
                if ring_r > 0:
                    ring_oval = self.create_oval(
                        hub.x - ring_r,
                        hub.y - ring_r,
                        hub.x + ring_r,
                        hub.y + ring_r,
                        fill=color,
                        outline="",
                        width=0,
                    )
                    oval_items.append(ring_oval)

            oval = oval_items[0] if oval_items else None
        else:
            oval = self.create_oval(
                hub.x - r,
                hub.y - r,
                hub.x + r,
                hub.y + r,
                fill=Color[str(hub.color).upper()].hex,
                width=2,
            )

        if str(hub.color).upper() == "RAINBOW":
            text_color = "#FFFFFF"
        else:
            text_color = get_complementary_color(
                Color[str(hub.color).upper()].hex
            )

        self.create_text(
            hub.x, hub.y, text=hub.max_drones, fill=text_color, tags="text"
        )

        if original_hub and oval:
            self.tag_bind(
                oval, "<Enter>", lambda e: self._show_tooltip(e, original_hub)
            )
            self.tag_bind(oval, "<Leave>", lambda e: self._hide_tooltip())

        return oval

    def create_edge(
        self, _from: Hub, _to: Hub, cap: int = 1, arrow_size: float = 1.5
    ) -> None:
        d1, d2, d3 = tuple(map(lambda x: arrow_size * x, (8, 10, 3)))
        r: float = Configure.text_padding * self._font[1]
        x0, y0 = _from.x, _from.y
        x1, y1 = _to.x, _to.y
        dx = x1 - x0
        dy = y1 - y0
        dist = sqrt(dx**2 + dy**2)
        if dist == 0:
            return
        start_x = x0 + (dx / dist) * r
        start_y = y0 + (dy / dist) * r
        end_x = x1 - (dx / dist) * r
        end_y = y1 - (dy / dist) * r

        line_id = self.create_line(
            start_x,
            start_y,
            end_x,
            end_y,
            arrow="both",
            fill=Configure.edge_color,
            width=1 * self._cscale,
            arrowshape=(d1, d2, d3),
        )
        self.edge_items.append(line_id)

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
            fill=Configure.foreground,
            angle=-atan2(dy, dx) * 57.295779513,
            tags="text",
        )

    def create_graph(self, adj_lst: dict[Hub, list[tuple[Hub, int]]]) -> None:
        nodes = list(adj_lst.keys())

        if not nodes:
            return

        x0_bbox: float = nodes[0].x
        x1_bbox: float = nodes[0].x
        y0_bbox: float = nodes[0].y
        y1_bbox: float = nodes[0].y

        for node in nodes:
            x, y = node.x, node.y
            x0_bbox = min(x0_bbox, x)
            y0_bbox = min(y0_bbox, y)
            x1_bbox = max(x1_bbox, x)
            y1_bbox = max(y1_bbox, y)

        width_bbox = x1_bbox - x0_bbox
        height_bbox = y1_bbox - y0_bbox

        scale_x: float
        scale_y: float
        if width_bbox == 0 and height_bbox == 0:
            scale_x = scale_y = 1.0
        elif width_bbox == 0:
            scale_x = scale_y = Configure.height / height_bbox * 0.9
        elif height_bbox == 0:
            scale_x = scale_y = Configure.width / width_bbox * 0.9
        else:
            scale_x = Configure.width / width_bbox * 0.9
            scale_y = Configure.height / height_bbox * 0.9

        x_c = (x0_bbox + x1_bbox) / 2
        y_c = (y0_bbox + y1_bbox) / 2

        node_positions: dict[Hub, tuple[float, float]] = {}
        for node in nodes:
            scaled_x = (node.x - x_c) * scale_x + Configure.width / 2
            scaled_y = -(node.y - y_c) * scale_y + Configure.height / 2
            node_positions[node] = (scaled_x, scaled_y)

        self.node_positions = node_positions

        drawn_edges = set()
        for from_node, neighbors in adj_lst.items():
            from_x, from_y = node_positions[from_node]
            for to_node, capacity in neighbors:
                edge_key = tuple(sorted([id(from_node), id(to_node)]))
                if edge_key not in drawn_edges:
                    to_x, to_y = node_positions[to_node]
                    from_hub_scaled = Hub(
                        from_node.type,
                        from_node.name,
                        int(from_x),
                        int(from_y),
                        zone=from_node.zone,
                        color=from_node.color,
                        max_drones=from_node.max_drones,
                    )
                    to_hub_scaled = Hub(
                        to_node.type,
                        to_node.name,
                        int(to_x),
                        int(to_y),
                        zone=to_node.zone,
                        color=to_node.color,
                        max_drones=to_node.max_drones,
                    )
                    self.create_edge(
                        from_hub_scaled,
                        to_hub_scaled,
                        capacity,
                        arrow_size=1.5 * self._cscale,
                    )
                    drawn_edges.add(edge_key)

        for node in nodes:
            x_coord, y_coord = node_positions[node]
            hub_scaled = Hub(
                node.type,
                node.name,
                int(x_coord),
                int(y_coord),
                zone=node.zone,
                color=node.color,
                max_drones=node.max_drones,
            )
            hub_item = self.create_vertex(hub_scaled, original_hub=node)
            if hub_item is not None:
                self.hub_items[node] = hub_item

    def get_current_hub_position(self, hub: Hub) -> tuple[float, float]:
        """Get current canvas position of a hub (accounts for pan/zoom)"""
        if hub not in self.hub_items:
            if hub.type == "transit" and hub.name.startswith("__transit__"):
                parts = hub.name.split("__")
                if len(parts) >= 5:
                    from_name = parts[2]
                    to_name = parts[3]
                    from_hub = next(
                        (h for h in self.hub_items if h.name == from_name),
                        None,
                    )
                    to_hub = next(
                        (h for h in self.hub_items if h.name == to_name),
                        None,
                    )
                    if from_hub and to_hub:
                        fx, fy = self.get_current_hub_position(from_hub)
                        tx, ty = self.get_current_hub_position(to_hub)
                        return ((fx + tx) / 2, (fy + ty) / 2)
            return self.node_positions.get(hub, (0, 0))

        hub_item = self.hub_items[hub]
        coords = self.coords(hub_item)
        if coords:
            x = (coords[0] + coords[2]) / 2
            y = (coords[1] + coords[3]) / 2
            return (x, y)
        return self.node_positions.get(hub, (0, 0))

    def create_drone(self, drone_id: int, hub: Hub) -> int:
        """Create a drone marker at a specific hub"""
        self.initial_positions[drone_id] = hub

        x, y = self.get_current_hub_position(hub)
        size = Configure.text_padding * self._font[1] * 0.5  # Drone size
        drone_item = self.create_oval(
            x - size,
            y - size,
            x + size,
            y + size,
            fill="#ff6b6b",
            outline="#ffffff",
            width=2,
            tags=("drone", f"drone_{drone_id}"),
        )

        text_item = self.create_text(
            x,
            y,
            text=str(drone_id),
            fill="white",
            font=("Arial", 8, "bold"),
            tags=("drone", f"drone_{drone_id}_label"),
        )

        self.drone_items[drone_id] = (drone_item, text_item)
        return drone_item

    def animate_drone(
        self,
        drone_id: int,
        from_hub: Hub,
        to_hub: Hub,
        step: int,
        total_steps: int,
    ) -> None:
        """Animate drone movement between hubs"""
        if drone_id not in self.drone_items:
            self.create_drone(drone_id, from_hub)

        from_x, from_y = self.get_current_hub_position(from_hub)
        to_x, to_y = self.get_current_hub_position(to_hub)

        progress = step / total_steps
        current_x = from_x + (to_x - from_x) * progress
        current_y = from_y + (to_y - from_y) * progress

        if drone_id in self.drone_items:
            drone_item, text_item = self.drone_items[drone_id]

            coords = self.coords(drone_item)
            if coords:
                old_x = (coords[0] + coords[2]) / 2
                old_y = (coords[1] + coords[3]) / 2
                dx = current_x - old_x
                dy = current_y - old_y

                self.move(drone_item, dx, dy)
                self.move(text_item, dx, dy)

    def set_animation_data(
        self, movements_per_turn: list[dict[int, tuple[Hub, Hub]]]
    ) -> None:
        """Set the movement data for animation"""
        self.animation_queue = movements_per_turn
        self.current_turn = 0

    def play_animation(self) -> None:
        """Start playing the animation automatically"""
        if self.is_animating or not self.animation_queue:
            return

        self.is_animating = True
        self.auto_play = True
        self.is_paused = False
        self._animate_step(0)

    def pause_animation(self) -> None:
        """Pause the animation"""
        self.is_paused = True
        self.auto_play = False

    def restart_animation(self) -> None:
        """Restart animation from the beginning"""
        self.is_animating = False
        self.is_paused = False
        self.auto_play = False
        self.current_turn = 0

        for drone_id in list(self.drone_items.keys()):
            if drone_id in self.initial_positions:
                start_hub = self.initial_positions[drone_id]
                x, y = self.get_current_hub_position(start_hub)
                self._move_drone_to(drone_id, x, y)

    def next_turn(self) -> None:
        """Move to the next turn"""
        if self.current_turn < len(self.animation_queue) - 1:
            self._execute_turn_instant(self.current_turn)
            self.current_turn += 1

    def previous_turn(self) -> None:
        """Move to the previous turn"""
        if self.current_turn > 0:
            target_turn = self.current_turn - 1
            self.restart_animation()
            for turn_idx in range(target_turn):
                self._execute_turn_instant(turn_idx)
            self.current_turn = target_turn

    def _move_drone_to(self, drone_id: int, x: float, y: float) -> None:
        """Move drone to specific coordinates instantly"""
        if drone_id in self.drone_items:
            drone_item, text_item = self.drone_items[drone_id]
            coords = self.coords(drone_item)
            if coords:
                old_x = (coords[0] + coords[2]) / 2
                old_y = (coords[1] + coords[3]) / 2
                dx = x - old_x
                dy = y - old_y
                self.move(drone_item, dx, dy)
                self.move(text_item, dx, dy)

    def _execute_turn_instant(self, turn_idx: int) -> None:
        """Execute a turn instantly without animation"""
        if turn_idx >= len(self.animation_queue):
            return

        turn_movements = self.animation_queue[turn_idx]
        for drone_id, (from_hub, to_hub) in turn_movements.items():
            x, y = self.get_current_hub_position(to_hub)
            self._move_drone_to(drone_id, x, y)

    def _animate_step(self, step: int) -> None:
        """Animate a single step of the current turn"""
        if not self.auto_play or self.current_turn >= len(
            self.animation_queue
        ):
            self.is_animating = False
            return

        turn_movements = self.animation_queue[self.current_turn]
        total_steps = Configure.animation_steps

        # On step 0, position drones at their starting positions for this turn
        if step == 0:
            for drone_id, (from_hub, to_hub) in turn_movements.items():
                x, y = self.get_current_hub_position(from_hub)
                self._move_drone_to(drone_id, x, y)

        for drone_id, (from_hub, to_hub) in turn_movements.items():
            self.animate_drone(drone_id, from_hub, to_hub, step, total_steps)

        if step < total_steps - 1:
            if self.auto_play:
                self.after(
                    Configure.animation_delay,
                    lambda: self._animate_step(step + 1),
                )
        else:
            self.current_turn += 1
            if (
                self.current_turn < len(self.animation_queue)
                and self.auto_play
            ):
                self.after(
                    Configure.animation_delay * 2,
                    lambda: self._animate_step(0),
                )
            else:
                self.is_animating = False
                self.auto_play = False
