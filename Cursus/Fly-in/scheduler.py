import logging
from simulation import Simulator
from collections import deque
from colors import Color, ColorStr
from graph import Hub, Graph


def edmonds_karp(
    capacity: list[list[int]], source: int, sink: int
) -> list[list[int]]:
    """
    Find maximum flow using BFS-based augmenting paths
    Returns flow matrix
    """
    n = len(capacity)
    flow = [[0] * n for _ in range(n)]

    def bfs_find_path() -> list[int] | None:
        """Find augmenting path using BFS"""
        visited = [False] * n
        parent = [-1] * n
        queue = deque([source])
        visited[source] = True

        while queue:
            u = queue.popleft()
            for v in range(n):
                if not visited[v] and capacity[u][v] > flow[u][v]:
                    visited[v] = True
                    parent[v] = u
                    queue.append(v)
                    if v == sink:
                        return parent
        return None

    while True:
        parent = bfs_find_path()
        if not parent:
            break

        path_flow = float("inf")
        v = sink
        while v != source:
            u = parent[v]
            path_flow = min(path_flow, capacity[u][v] - flow[u][v])
            v = u

        path_flow = int(path_flow)
        v = sink
        while v != source:
            u = parent[v]
            flow[u][v] += path_flow
            flow[v][u] -= path_flow
            v = u

    return flow


class PathPlanner:
    def __init__(self, graph: Graph, nb_drones: int):
        self.graph = graph
        self.nb_drones = nb_drones
        self.start = graph.start
        self.goal = graph.end

    def assign_drones(self) -> dict[int, list[Hub]]:
        """Main planning logic using k-shortest paths + max-flow assignment"""
        if not self.start or not self.goal:
            raise ValueError("Start or goal hub not found in graph")

        k = min(5, self.nb_drones)
        paths = self.graph.k_shortest_paths(self.start, self.goal, k)

        paths = [
            p
            for p in paths
            if len(p) > 1 and p[0] == self.start and p[-1] == self.goal
        ]

        if not paths:
            _, simple_path = self.graph.dijkstra(self.start, self.goal)
            if simple_path and len(simple_path) > 1:
                paths = [simple_path]
            else:
                raise ValueError("No valid path found from start to goal")

        num_paths = len(paths)
        capacity_matrix = [[0] * (num_paths + 2) for _ in range(num_paths + 2)]

        source = 0
        sink = num_paths + 1

        for i, path in enumerate(paths):
            path_node = i + 1
            bottleneck = self.graph.get_path_capacity(path)
            capacity_matrix[source][path_node] = min(
                self.nb_drones, bottleneck
            )

        for i, path in enumerate(paths):
            path_node = i + 1
            bottleneck = self.graph.get_path_capacity(path)
            capacity_matrix[path_node][sink] = bottleneck

        flow = edmonds_karp(capacity_matrix, source, sink)

        assignments = {}
        drone_id = 1
        for i, path in enumerate(paths):
            path_node = i + 1
            drones_on_path = int(flow[source][path_node])

            for _ in range(drones_on_path):
                if drone_id <= self.nb_drones:
                    assignments[drone_id] = path
                    drone_id += 1

        while drone_id <= self.nb_drones:
            valid_path = next((p for p in paths if len(p) > 1), None)
            if valid_path:
                assignments[drone_id] = valid_path
                drone_id += 1
            else:
                break

        return assignments


class Scheduler:
    """Turn-by-turn movement scheduling
    - resolve conflicts
    - manage waiting strategies
    - optimize for minimal turns
    """

    def __init__(
        self,
        simulator: Simulator,
        assignments: dict[int, list[Hub]],
        visual: bool = False,
    ):
        self.simulator = simulator
        self.assignments = assignments
        self.logger = logging.getLogger("scheduler")
        self.visual = visual
        self.movements_per_turn: list[dict[int, tuple[Hub, Hub]]] = []

    def schedule_and_run(self) -> list[dict[int, tuple[Hub, Hub]]]:
        """
        Execute simulation turn-by-turn following assigned paths.
        Handles capacity constraints and strategic waiting.
        """
        drone_progress = {d_id: 0 for d_id in self.assignments}
        transit_midpoints: dict[int, Hub] = {}

        while not self.simulator.is_complete():
            moves = {}
            connection_usage: dict[tuple[Hub, Hub], int] = {}
            planned_from_by_id: dict[int, Hub] = {}
            # Track drones leaving and entering each hub this turn
            leaving_hub: dict[Hub, int] = {}
            entering_hub: dict[Hub, int] = {}

            for drone in self.simulator.drones:
                if drone.state == "delivered" or drone.state == "in_transit":
                    continue

                path = self.assignments.get(drone.id)
                if not path:
                    self.logger.warning(
                        f"Drone {drone.id} has no assigned path"
                    )
                    continue

                if len(path) <= 1:
                    self.logger.warning(
                        f"Drone {drone.id} of invalid path (len={len(path)})"
                    )
                    continue

                progress = drone_progress[drone.id]

                if progress >= len(path) - 1:
                    continue

                next_hub = path[progress + 1]
                current_hub = drone.hub

                # Calculate effective capacity considering moves this turn
                current_occupancy = self.simulator.get_hub_occupancy(next_hub)
                drones_leaving = leaving_hub.get(next_hub, 0)
                drones_entering = entering_hub.get(next_hub, 0)
                effective_occupancy = (
                    current_occupancy - drones_leaving + drones_entering
                )

                # Check capacity (start/end hubs have unlimited capacity)
                can_enter = (
                    next_hub == self.simulator.end_hub
                    or next_hub == self.simulator.start_hub
                    or effective_occupancy < next_hub.max_drones
                )

                if not can_enter:
                    continue

                connection_key = (current_hub, next_hub)
                connection_capacity = self.simulator.get_connection_capacity(
                    current_hub, next_hub
                )
                current_connection_usage = connection_usage.get(
                    connection_key, 0
                )

                if current_connection_usage < connection_capacity:
                    moves[drone] = next_hub
                    planned_from_by_id[drone.id] = current_hub
                    connection_usage[connection_key] = (
                        current_connection_usage + 1
                    )

                    # Track hub occupancy changes
                    if current_hub != self.simulator.start_hub:
                        leaving_hub[current_hub] = (
                            leaving_hub.get(current_hub, 0) + 1
                        )
                    entering_hub[next_hub] = entering_hub.get(next_hub, 0) + 1

            turn_output = self.simulator.simulate_turn(moves)
            if turn_output:
                if self.visual:
                    self._print_colored_turn(self.simulator.graph, turn_output)
                else:
                    print(turn_output)

            if self.visual and turn_output:
                turn_movements = {}
                for movement_str in turn_output.split():
                    parts = movement_str.split("-")
                    if len(parts) < 2:
                        continue

                    drone_id_str = parts[0]
                    if not drone_id_str.startswith("D"):
                        continue

                    try:
                        drone_id = int(drone_id_str[1:])
                    except ValueError:
                        continue

                    if len(parts) == 3:
                        from_name = parts[1]
                        to_name = parts[2]

                        from_hub_opt = next(
                            (
                                h
                                for h in self.simulator.graph.adj_lst
                                if h.name == from_name
                            ),
                            None,
                        )
                        to_hub_opt = next(
                            (
                                h
                                for h in self.simulator.graph.adj_lst
                                if h.name == to_name
                            ),
                            None,
                        )

                        if from_hub_opt and to_hub_opt:
                            mid_hub = Hub(
                                "transit",
                                (
                                    "__transit__"
                                    f"{from_hub_opt.name}__{to_hub_opt.name}"
                                    f"__{drone_id}__{self.simulator.turn}"
                                ),
                                int((from_hub_opt.x + to_hub_opt.x) / 2),
                                int((from_hub_opt.y + to_hub_opt.y) / 2),
                                zone=to_hub_opt.zone,
                                color=to_hub_opt.color,
                                max_drones=1,
                            )
                            turn_movements[drone_id] = (from_hub_opt, mid_hub)
                            transit_midpoints[drone_id] = mid_hub
                    else:
                        to_name = "-".join(parts[1:])
                        to_hub_opt = next(
                            (
                                h
                                for h in self.simulator.graph.adj_lst
                                if h.name == to_name
                            ),
                            None,
                        )

                        if not to_hub_opt:
                            continue

                        if drone_id in transit_midpoints:
                            from_hub_opt = transit_midpoints.pop(drone_id)
                        else:
                            from_hub_opt = planned_from_by_id.get(drone_id)

                        if from_hub_opt:
                            turn_movements[drone_id] = (
                                from_hub_opt,
                                to_hub_opt,
                            )

                if turn_movements:
                    self.movements_per_turn.append(turn_movements)

            for drone in self.simulator.drones:
                path = self.assignments.get(drone.id)
                if not path:
                    continue

                progress = drone_progress[drone.id]
                if (
                    progress + 1 < len(path)
                    and drone.hub == path[progress + 1]
                ):
                    drone_progress[drone.id] = progress + 1

        return self.movements_per_turn

    def get_movements_for_animation(self) -> list[dict[int, tuple[Hub, Hub]]]:
        """Return the recorded movements for animation"""
        return self.movements_per_turn

    def _print_colored_turn(self, graph: Graph, turn_output: str) -> None:
        """Print turn output with colored drone movements"""
        movements = turn_output.strip().split()
        colored_movements = []

        for movement in movements:
            # Parse movement: D<id>-<zone> or D<id>-<connection>
            #   - 🟢 **Green**: Start/End zones
            #   - 🔵 **Blue**: Normal paths
            #   - 🟡 **Yellow**: Junction/merge points
            #   - 🟠 **Orange**: Bottlenecks/gates
            #   - 🔴 **Red**: Dead ends/traps
            #   - 🟣 **Purple**: Restricted zones
            #   - 🔵 **Cyan**: Priority zones

            d, z1, *z2 = movement.split("-")
            c_z1 = next((h.color for h in graph.adj_lst if h.name == z1))

            if c_z1:
                move = ColorStr(f"{d}-{z1}", fg=Color[c_z1.upper()])

            if z2:
                z2_str = z2[0]
                c_z2 = next(
                    (h.color for h in graph.adj_lst if h.name == z2_str), None
                )
                if c_z2:
                    move = ColorStr(
                        f"{d}-{z1}-{z2_str}", fg=Color[c_z2.upper()]
                    )

            colored_movements.append(move)

        print(" ".join(str(m) for m in colored_movements))
