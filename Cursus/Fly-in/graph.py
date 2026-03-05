from enum import Enum
from heapq import heappop, heappush
from typing import Iterator


class Zone(Enum):
    NORMAL = "normal"
    BLOCKED = "blocked"
    RESTRICTED = "restricted"
    PRIORITY = "priority"


class Drone:
    def __init__(self, id: int, hub: "Hub") -> None:
        self.id = id
        self.hub = hub
        self.path: list[Hub]
        self.state: str

    @property
    def position(self) -> str:
        return f"D{self.id}-{self.hub}"


class Hub:
    def __init__(
        self,
        htype: str,
        name: str,
        x: int,
        y: int,
        zone: Zone | str = Zone.NORMAL,
        color: str | None = None,
        max_drones: int = 1,
    ) -> None:
        self.type = htype
        self.name = name
        self.x = x
        self.y = y
        if isinstance(zone, str):
            try:
                self.zone = Zone[zone.upper()]
            except KeyError:
                raise ValueError(f"Invalid zone type: {zone}")
        else:
            self.zone = zone
        self.color = color
        self.max_drones = max_drones
        self.drones: list[Drone] = []

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Hub):
            return NotImplemented
        return all(
            (
                self.name == other.name,
                self.x == other.x,
                self.y == other.y,
                self.zone == other.zone,
                self.max_drones == other.max_drones,
            )
        )

    def __hash__(self) -> int:
        return hash((self.name, self.x, self.y, self.zone, self.max_drones))

    def __lt__(self, other: object) -> bool:
        """Enable comparison for heap operations in Dijkstra"""
        if not isinstance(other, Hub):
            return NotImplemented
        return self.name < other.name

    def __str__(self) -> str:
        return f"{self.name}"

    def __repr__(self) -> str:
        return (
            f"Hub({self.name}, x={self.x}, y={self.y}, zone={self.zone}, "
            f"color={self.color}, max_drones={self.max_drones})"
        )


class Graph:
    """
    Graph data structure represented by an adjacency list
    """

    def __init__(self) -> None:
        self.adj_lst: dict[Hub, list[tuple[Hub, int]]] = {}

    def add_vertex(self, hub: Hub) -> None:
        if hub not in self.adj_lst:
            self.adj_lst[hub] = []

    def add_edge(self, from_vert: Hub, to_vert: Hub, cap: int = 1) -> None:
        self.add_vertex(from_vert)
        self.add_vertex(to_vert)
        self.adj_lst[from_vert].append((to_vert, cap))
        self.adj_lst[to_vert].append((from_vert, cap))

    @property
    def start(self) -> Hub | None:
        for vertex in self.adj_lst:
            if vertex.type == "start_hub":
                return vertex
        return None

    @property
    def end(self) -> Hub | None:
        for vertex in self.adj_lst:
            if vertex.type == "end_hub":
                return vertex
        return None

    def get_neighbors(self, hub: Hub) -> list[tuple[Hub, int]]:
        return self.adj_lst.get(hub, [])

    def get_edge_cost(self, to_hub: Hub) -> float:
        """Calculate cost considering zone types"""
        base_cost = 1.0

        if to_hub.zone == Zone.BLOCKED:
            return float("inf")
        elif to_hub.zone == Zone.RESTRICTED:
            base_cost = 2.0
        elif to_hub.zone == Zone.PRIORITY:
            base_cost = 0.5
        elif to_hub.zone == Zone.NORMAL:
            base_cost = 1.0
        return base_cost

    def get_edge_capacity(self, from_hub: Hub, to_hub: Hub) -> int:
        """Get max_link_capacity for a connection"""
        neighbors = self.get_neighbors(from_hub)
        for neighbor, capacity in neighbors:
            if neighbor == to_hub:
                return capacity
        return 1

    def get_path_capacity(self, path: list[Hub]) -> int:
        """
        Find the minimum capacity along a path (the bottleneck)
        """
        if len(path) < 2:
            return 999999
        min_capacity = float("inf")

        for hub in path[1:-1]:
            min_capacity = min(min_capacity, hub.max_drones)

        for i in range(len(path) - 1):
            connection_cap = self.get_edge_capacity(path[i], path[i + 1])
            min_capacity = min(min_capacity, connection_cap)

        if min_capacity == float("inf"):
            return 999999

        return int(min_capacity)

    def build_from_tokens(self, tokens: list[dict[str, str | int]]) -> None:
        for token in tokens:
            token_type = token.get("type")

            if token_type and str(token_type).endswith("hub"):
                self.add_vertex(
                    Hub(
                        htype=str(token_type),
                        name=str(token["name"]),
                        x=int(token["x"]),
                        y=int(token["y"]),
                        zone=str(token.get("zone", Zone.NORMAL.value)),
                        color=str(token["color"])
                        if token.get("color")
                        else None,
                        max_drones=int(token.get("max_drones", 1)),
                    )
                )

            elif token_type == "connection":
                from_hub = next(
                    (
                        hub
                        for hub in self.adj_lst
                        if hub.name == token.get("from")
                    ),
                    None,
                )

                to_hub = next(
                    (
                        hub
                        for hub in self.adj_lst
                        if hub.name == token.get("to")
                    ),
                    None,
                )

                if from_hub is None or to_hub is None:
                    raise ValueError(f"Hub not found for connection: {token}")

                capacity = token.get("max_link_capacity", 1)
                self.add_edge(from_hub, to_hub, int(capacity))

    def dijkstra(self, start: Hub, end: Hub) -> tuple[float, list[Hub]]:
        distances = {node: float("inf") for node in self.adj_lst}
        previous = {}
        distances[start] = 0.0
        pq = [(0.0, start)]

        while pq:
            current_dist, current = heappop(pq)

            if current == end:
                break

            if current_dist > distances[current]:
                continue

            for neighbor, _ in self.adj_lst[current]:
                # Use zone-aware cost instead of raw capacity
                edge_cost = self.get_edge_cost(neighbor)
                distance = current_dist + edge_cost
                if distance < distances[neighbor]:
                    distances[neighbor] = distance
                    previous[neighbor] = current
                    heappush(pq, (distance, neighbor))

        path = []
        current = end
        while current in previous:
            path.append(current)
            current = previous[current]
        path.append(start)
        path.reverse()
        return distances[end], path

    def k_shortest_paths(
        self, start: Hub, goal: Hub, k: int
    ) -> list[list[Hub]]:
        """
        Find k diverse paths using Yen's algorithm with zone-aware costs
        """
        if not start or not goal:
            return []

        paths = []
        candidates = []

        _, shortest = self.dijkstra(start, goal)
        if not shortest or len(shortest) < 2:
            return []
        paths.append(shortest)

        for k_iter in range(1, k):
            for i in range(len(paths[-1]) - 1):
                spur_node = paths[-1][i]
                root_path = paths[-1][: i + 1]

                removed_edges = []

                for path in paths:
                    if len(path) > i and path[: i + 1] == root_path:
                        if i + 1 < len(path):
                            edge = (path[i], path[i + 1])
                            removed_edges.append(edge)
                            self.adj_lst[path[i]] = [
                                (n, c)
                                for n, c in self.adj_lst[path[i]]
                                if n != path[i + 1]
                            ]
                            self.adj_lst[path[i + 1]] = [
                                (n, c)
                                for n, c in self.adj_lst[path[i + 1]]
                                if n != path[i]
                            ]

                _, spur_path = self.dijkstra(spur_node, goal)

                for from_hub, to_hub in removed_edges:
                    cap = self.get_edge_capacity(from_hub, to_hub) or 1
                    self.adj_lst[from_hub].append((to_hub, cap))
                    self.adj_lst[to_hub].append((from_hub, cap))

                if spur_path and len(spur_path) > 0:
                    total_path = root_path[:-1] + spur_path
                    if (
                        total_path not in candidates
                        and total_path not in paths
                    ):
                        candidates.append(total_path)

            if not candidates:
                break

            candidates.sort(
                key=lambda p: sum(
                    self.get_edge_cost(p[i + 1]) for i in range(len(p) - 1)
                )
            )
            paths.append(candidates.pop(0))

        return paths

    def __iter__(self) -> "Iterator[Hub]":
        return iter(self.adj_lst.keys())

    def __repr__(self) -> str:
        num_vertices = len(self.adj_lst)
        num_edges = (
            sum(len(neighbors) for neighbors in self.adj_lst.values()) // 2
        )
        return f"Graph(vertices={num_vertices}, edges={num_edges})"

    def __str__(self) -> str:
        if not len(self.adj_lst):
            return "{}"

        from io import StringIO

        buf = StringIO()
        buf.write("{\n")
        outer_i = 0
        for k, list_v in self.adj_lst.items():
            buf.write(f"    {str(k)}: ")
            if not len(list_v):
                buf.write("[]")
                buf.write(",\n" if outer_i < len(self.adj_lst) - 1 else "\n")
            elif len(list_v) == 1:
                buf.write(f"[({str(list_v[0][0])}, {list_v[0][1]})]")
                buf.write(",\n" if outer_i < len(self.adj_lst) - 1 else "\n")
            else:
                buf.write("[\n")
                for inner_i, v in enumerate(list_v):
                    buf.write(f"        ({str(v[0])}, {v[1]})")
                    if inner_i < len(list_v) - 1:
                        buf.write(",\n")
                    else:
                        buf.write("\n")
                buf.write("    ]")
                buf.write(",\n" if outer_i < len(self.adj_lst) - 1 else "\n")
            outer_i += 1
        buf.write("}\n")

        return buf.getvalue()
