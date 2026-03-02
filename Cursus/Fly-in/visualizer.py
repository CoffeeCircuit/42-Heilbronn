import tkinter as tk
from config import Configure
from graph import Hub
from colors import Color
from math import sqrt, atan2


def get_complementary_color(hex_color: str) -> str:
    """Calculate complementary color for contrast"""
    # Remove # if present
    hex_color = hex_color.lstrip("#")

    # Convert to RGB
    r = int(hex_color[0:2], 16)
    g = int(hex_color[2:4], 16)
    b = int(hex_color[4:6], 16)

    # Calculate luminance (perceived brightness)
    luminance = (0.299 * r + 0.587 * g + 0.114 * b) / 255

    # If dark background, use white; if light, use black
    # This provides better readability than pure complementary
    if luminance < 0.5:
        return "#FFFFFF"
    else:
        return "#000000"


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

        # Animation tracking
        self.node_positions = {}
        self.hub_items = {}  # hub -> canvas item for tracking position after transforms
        self.drone_items = {}  # drone_id -> canvas item
        self.edge_items = []  # list of edge canvas item IDs for updating arrowshapes
        self.animation_queue = []
        self.current_turn = 0
        self.is_animating = False
        self.is_paused = False
        self.auto_play = False
        self.initial_positions = {}  # Store initial drone positions
        self.tooltip = None  # Tooltip widget

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
            scale_factor = self._sc_up
        elif event.num == 5:
            self._cscale *= self._sc_down
            self.scale("all", event.x, event.y, self._sc_down, self._sc_down)
            scale_factor = self._sc_down
        else:
            return

        self._font = (self._font[0], int(Configure.font[1] * self._cscale))
        self.itemconfig("text", font=self._font)

        # Update arrow shapes to match new scale
        base_arrow_size = 1.5 * self._cscale
        d1, d2, d3 = tuple(map(lambda x: base_arrow_size * x, (8, 10, 3)))
        for edge_id in self.edge_items:
            self.itemconfig(
                edge_id, arrowshape=(d1, d2, d3), width=2 * self._cscale
            )

    def _show_tooltip(self, event, hub: Hub):
        """Show tooltip with hub information"""
        self._hide_tooltip()  # Hide any existing tooltip

        # Create tooltip window
        self.tooltip = tk.Toplevel(self)
        self.tooltip.wm_overrideredirect(True)  # Remove window decorations
        self.tooltip.wm_geometry(f"+{event.x_root + 10}+{event.y_root + 10}")

        # Create tooltip content
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

    def _hide_tooltip(self):
        """Hide the tooltip"""
        if self.tooltip:
            self.tooltip.destroy()
            self.tooltip = None

    def create_vertex(self, hub: Hub, original_hub: Hub = None):
        r = Configure.text_padding * self._font[1]

        # Check if this is a rainbow color
        if str(hub.color).upper() == "RAINBOW":
            # Create rainbow effect with concentric circles
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

        # Determine text color based on hub color
        if str(hub.color).upper() == "RAINBOW":
            text_color = "#FFFFFF"  # White for rainbow
        else:
            text_color = get_complementary_color(
                Color[str(hub.color).upper()].hex
            )

        self.create_text(
            hub.x, hub.y, text=hub.max_drones, fill=text_color, tags="text"
        )

        # Bind tooltip events if we have the original hub
        if original_hub and oval:
            self.tag_bind(
                oval, "<Enter>", lambda e: self._show_tooltip(e, original_hub)
            )
            self.tag_bind(oval, "<Leave>", lambda e: self._hide_tooltip())

        return oval

    def create_edge(self, _from: Hub, _to: Hub, cap: int = 1, arrow_size=1.5):
        d1, d2, d3 = tuple(map(lambda x: arrow_size * x, (8, 10, 3)))
        r = Configure.text_padding * self._font[1]
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

    def create_graph(self, adj_lst: dict[Hub, list[tuple[Hub, int]]]):
        # Extract nodes from adjacency list
        nodes = list(adj_lst.keys())

        if not nodes:
            return

        # Initialize to first node
        x0_bbox = x1_bbox = nodes[0].x
        y0_bbox = y1_bbox = nodes[0].y

        for node in nodes:
            x, y = node.x, node.y
            x0_bbox = min(x0_bbox, x)
            y0_bbox = min(y0_bbox, y)
            x1_bbox = max(x1_bbox, x)
            y1_bbox = max(y1_bbox, y)

        # Handle single point or line cases
        width_bbox = x1_bbox - x0_bbox
        height_bbox = y1_bbox - y0_bbox

        if width_bbox == 0 and height_bbox == 0:
            scale_x = scale_y = 1
        elif width_bbox == 0:
            scale_x = scale_y = Configure.height / height_bbox * 0.9
        elif height_bbox == 0:
            scale_x = scale_y = Configure.width / width_bbox * 0.9
        else:
            # Use independent scaling for x and y to fill the window
            scale_x = Configure.width / width_bbox * 0.9
            scale_y = Configure.height / height_bbox * 0.9

        # Center of nodes
        x_c = (x0_bbox + x1_bbox) / 2
        y_c = (y0_bbox + y1_bbox) / 2

        # Create a mapping from original nodes to scaled positions
        node_positions = {}
        for node in nodes:
            scaled_x = (node.x - x_c) * scale_x + Configure.width / 2
            # Invert y-axis: screen coordinates increase downward, graph coordinates increase upward
            scaled_y = -(node.y - y_c) * scale_y + Configure.height / 2
            node_positions[node] = (scaled_x, scaled_y)

        # Store for animation
        self.node_positions = node_positions

        # Draw edges first (so they appear behind vertices)
        drawn_edges = set()
        for from_node, neighbors in adj_lst.items():
            from_x, from_y = node_positions[from_node]
            for to_node, capacity in neighbors:
                # Avoid drawing duplicate edges for undirected graph
                edge_key = tuple(sorted([id(from_node), id(to_node)]))
                if edge_key not in drawn_edges:
                    to_x, to_y = node_positions[to_node]
                    # Create temporary Hub objects with scaled coordinates
                    from_hub_scaled = Hub(
                        from_node.type,
                        from_node.name,
                        from_x,
                        from_y,
                        zone=from_node.zone,
                        color=from_node.color,
                        max_drones=from_node.max_drones,
                    )
                    to_hub_scaled = Hub(
                        to_node.type,
                        to_node.name,
                        to_x,
                        to_y,
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

        # Draw vertices on top
        for node in nodes:
            x, y = node_positions[node]
            # Create temporary Hub object with scaled coordinates
            hub_scaled = Hub(
                node.type,
                node.name,
                x,
                y,
                zone=node.zone,
                color=node.color,
                max_drones=node.max_drones,
            )
            hub_item = self.create_vertex(hub_scaled, original_hub=node)
            self.hub_items[node] = hub_item

    def get_current_hub_position(self, hub: Hub):
        """Get current canvas position of a hub (accounts for pan/zoom)"""
        if hub not in self.hub_items:
            # Fallback to stored position
            return self.node_positions.get(hub, (0, 0))

        hub_item = self.hub_items[hub]
        coords = self.coords(hub_item)
        if coords:
            # Return center of the oval
            x = (coords[0] + coords[2]) / 2
            y = (coords[1] + coords[3]) / 2
            return (x, y)
        return self.node_positions.get(hub, (0, 0))

    def create_drone(self, drone_id: int, hub: Hub):
        """Create a drone marker at a specific hub"""
        # Store initial position for restart
        self.initial_positions[drone_id] = hub

        x, y = self.get_current_hub_position(hub)
        size = Configure.text_padding * self._font[1] * 0.5  # Drone size
        # Create drone as a small colored circle
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

        # Add drone ID label
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
    ):
        """Animate drone movement between hubs"""
        if drone_id not in self.drone_items:
            # Create drone if it doesn't exist
            self.create_drone(drone_id, from_hub)

        # Get current canvas positions (accounts for pan/zoom)
        from_x, from_y = self.get_current_hub_position(from_hub)
        to_x, to_y = self.get_current_hub_position(to_hub)

        # Linear interpolation
        progress = step / total_steps
        current_x = from_x + (to_x - from_x) * progress
        current_y = from_y + (to_y - from_y) * progress

        # Move drone and its label
        if drone_id in self.drone_items:
            drone_item, text_item = self.drone_items[drone_id]

            # Get current position
            coords = self.coords(drone_item)
            if coords:
                old_x = (coords[0] + coords[2]) / 2
                old_y = (coords[1] + coords[3]) / 2
                dx = current_x - old_x
                dy = current_y - old_y

                self.move(drone_item, dx, dy)
                self.move(text_item, dx, dy)

    def set_animation_data(self, movements_per_turn: list[dict]):
        """Set the movement data for animation"""
        self.animation_queue = movements_per_turn
        self.current_turn = 0

    def play_animation(self):
        """Start playing the animation automatically"""
        if self.is_animating or not self.animation_queue:
            return

        self.is_animating = True
        self.auto_play = True
        self.is_paused = False
        self._animate_step(0)

    def pause_animation(self):
        """Pause the animation"""
        self.is_paused = True
        self.auto_play = False

    def restart_animation(self):
        """Restart animation from the beginning"""
        self.is_animating = False
        self.is_paused = False
        self.auto_play = False
        self.current_turn = 0

        # Reset all drones to initial positions
        for drone_id in list(self.drone_items.keys()):
            if drone_id in self.initial_positions:
                start_hub = self.initial_positions[drone_id]
                x, y = self.get_current_hub_position(start_hub)
                self._move_drone_to(drone_id, x, y)

    def next_turn(self):
        """Move to the next turn"""
        if self.current_turn < len(self.animation_queue) - 1:
            self._execute_turn_instant(self.current_turn)
            self.current_turn += 1

    def previous_turn(self):
        """Move to the previous turn"""
        if self.current_turn > 0:
            target_turn = self.current_turn - 1
            self.restart_animation()
            for turn_idx in range(target_turn):
                self._execute_turn_instant(turn_idx)
            self.current_turn = target_turn

    def _move_drone_to(self, drone_id: int, x: float, y: float):
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

    def _execute_turn_instant(self, turn_idx: int):
        """Execute a turn instantly without animation"""
        if turn_idx >= len(self.animation_queue):
            return

        turn_movements = self.animation_queue[turn_idx]
        for drone_id, (from_hub, to_hub) in turn_movements.items():
            x, y = self.get_current_hub_position(to_hub)
            self._move_drone_to(drone_id, x, y)

    def _animate_step(self, step: int):
        """Animate a single step of the current turn"""
        if not self.auto_play or self.current_turn >= len(
            self.animation_queue
        ):
            self.is_animating = False
            return

        turn_movements = self.animation_queue[self.current_turn]
        total_steps = Configure.animation_steps

        # Animate all drones in this turn
        for drone_id, (from_hub, to_hub) in turn_movements.items():
            self.animate_drone(drone_id, from_hub, to_hub, step, total_steps)

        if step < total_steps - 1:
            # Continue animation for this turn
            if self.auto_play:
                self.after(
                    Configure.animation_delay,
                    lambda: self._animate_step(step + 1),
                )
        else:
            # Move to next turn
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
