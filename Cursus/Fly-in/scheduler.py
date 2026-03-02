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

    def bfs_find_path():
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

    # Keep finding augmenting paths
    while True:
        parent = bfs_find_path()
        if not parent:
            break

        # Find bottleneck capacity
        path_flow = float("inf")
        v = sink
        while v != source:
            u = parent[v]
            path_flow = min(path_flow, capacity[u][v] - flow[u][v])
            v = u

        # Update flow along path
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

        # Filter out invalid paths (must start at start and end at goal)
        paths = [
            p
            for p in paths
            if len(p) > 1 and p[0] == self.start and p[-1] == self.goal
        ]

        # Fallback to simple Dijkstra if k-shortest fails or returns no valid paths
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

        # Source to each path: capacity = min(nb_drones, path_bottleneck)
        for i, path in enumerate(paths):
            path_node = i + 1
            bottleneck = self.graph.get_path_capacity(path)
            capacity_matrix[source][path_node] = min(
                self.nb_drones, bottleneck
            )

        # Each path to sink: capacity = path_bottleneck
        for i, path in enumerate(paths):
            path_node = i + 1
            bottleneck = self.graph.get_path_capacity(path)
            capacity_matrix[path_node][sink] = bottleneck

        # Run max-flow (Ford-Fulkerson or Edmonds-Karp)
        flow = edmonds_karp(capacity_matrix, source, sink)

        # Extract assignments: how many drones per path
        assignments = {}
        drone_id = 1
        for i, path in enumerate(paths):
            path_node = i + 1
            drones_on_path = int(flow[source][path_node])

            for _ in range(drones_on_path):
                if drone_id <= self.nb_drones:
                    assignments[drone_id] = path
                    drone_id += 1

        # Fallback: if not all drones assigned, assign remaining to first valid path
        while drone_id <= self.nb_drones:
            # Find first valid path (length > 1)
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
        self.movements_per_turn = []  # Track movements for animation

    def schedule_and_run(self) -> str:
        """
        Execute simulation turn-by-turn following assigned paths.
        Handles capacity constraints and strategic waiting.
        """
        # Track progress on each drone's path
        drone_progress = {d_id: 0 for d_id in self.assignments}

        while not self.simulator.is_complete():
            moves = {}
            # Track connection usage this turn: (from_hub, to_hub) -> count
            connection_usage = {}

            # Plan moves for all drones
            for drone in self.simulator.drones:
                if drone.state == "delivered" or drone.state == "in_transit":
                    continue

                # Get assigned path
                path = self.assignments.get(drone.id)
                if not path:
                    self.logger.warning(
                        f"Drone {drone.id} has no assigned path"
                    )
                    continue

                if len(path) <= 1:
                    self.logger.warning(
                        f"Drone {drone.id} has invalid path (length={len(path)})"
                    )
                    continue

                # Get current progress
                progress = drone_progress[drone.id]

                # Check if already at goal
                if progress >= len(path) - 1:
                    continue

                # Next hub in path
                next_hub = path[progress + 1]

                # Check if we can move (capacity available)
                if not self.simulator.can_move_to_hub(next_hub):
                    continue

                # Check connection capacity
                current_hub = drone.hub
                connection_key = (current_hub, next_hub)
                connection_capacity = self.simulator.get_connection_capacity(
                    current_hub, next_hub
                )
                current_connection_usage = connection_usage.get(
                    connection_key, 0
                )

                # Only allow move if connection has capacity
                if current_connection_usage < connection_capacity:
                    moves[drone] = next_hub
                    connection_usage[connection_key] = (
                        current_connection_usage + 1
                    )
                # Otherwise drone waits this turn

            # Track movements for animation (BEFORE executing the turn)
            if self.visual:
                turn_movements = {}
                for drone, to_hub in moves.items():
                    # Get the from_hub (current position before move)
                    from_hub = drone.hub
                    turn_movements[drone.id] = (from_hub, to_hub)
                if turn_movements:
                    self.movements_per_turn.append(turn_movements)

            # Execute turn with planned moves
            turn_output = self.simulator.simulate_turn(moves)

            # Print colored output if visual mode enabled
            if self.visual and turn_output:
                self._print_colored_turn(self.simulator.graph, turn_output)

            # Update progress for drones that successfully moved
            for drone in self.simulator.drones:
                path = self.assignments.get(drone.id)
                if not path:
                    continue

                progress = drone_progress[drone.id]
                # Check if drone moved to next position in path
                if (
                    progress + 1 < len(path)
                    and drone.hub == path[progress + 1]
                ):
                    drone_progress[drone.id] = progress + 1

        return self.simulator.get_output()

    def get_movements_for_animation(self) -> list[dict]:
        """Return the recorded movements for animation"""
        return self.movements_per_turn

    def _print_colored_turn(self, graph: Graph, turn_output: str):
        """Print turn output with colored drone movements based on zone types"""
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
                z2 = next(z2.__iter__())
                c_z2 = next((h.color for h in graph.adj_lst if h.name == z2))
                if c_z2:
                    move = ColorStr(f"{d}-{z1}-{z2}", fg=Color[c_z2.upper()])

            colored_movements.append(move)

        print(" ".join(str(m) for m in colored_movements))
