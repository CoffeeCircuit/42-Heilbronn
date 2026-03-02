from graph import Hub, Drone, Graph, Zone
from typing import Optional
from colors import Color, ColorStr


class Simulator:
    """Manages turn-by-turn simulation state
    - track drone positions per turn
    - validate moves against capacity
    - handle restricted zone (2-turn) movements
    - output formatted results
    """

    def __init__(self, graph: Graph, nb_drones: int):
        self.graph = graph
        self.nb_drones = nb_drones
        self.drones: list[Drone] = []
        self.turn = 0
        self.movements: list[str] = []  # Track all turn outputs

        # Find start and end hubs
        self.start_hub: Optional[Hub] = None
        self.end_hub: Optional[Hub] = None

        for hub in graph.adj_lst.keys():
            if hub.type == "start_hub":
                self.start_hub = hub
            elif hub.type == "end_hub":
                self.end_hub = hub

        if not self.start_hub or not self.end_hub:
            raise ValueError("Graph must have start_hub and end_hub")

        # Initialize drones at start
        for i in range(1, nb_drones + 1):
            drone = Drone(i, self.start_hub)
            drone.path = []
            drone.state = "waiting"  # waiting, moving, in_transit, delivered
            self.drones.append(drone)
            self.start_hub.drones.append(drone)

        # Track drones in transit to restricted zones
        self.in_transit: dict[
            Drone, tuple[Hub, Hub]
        ] = {}  # drone -> (from, to)

    def get_hub_occupancy(self, hub: Hub) -> int:
        """Get current number of drones in a hub"""
        return len(
            [
                d
                for d in self.drones
                if d.hub == hub and d.state != "in_transit"
            ]
        )

    def can_move_to_hub(self, hub: Hub, num_drones: int = 1) -> bool:
        """Check if hub has capacity for additional drones"""
        if hub == self.end_hub or hub == self.start_hub:
            return True

        current = self.get_hub_occupancy(hub)
        return current + num_drones <= hub.max_drones

    def get_connection_capacity(self, from_hub: Hub, to_hub: Hub) -> int:
        """Get max capacity of connection between two hubs"""
        for neighbor, cap in self.graph.get_neighbors(from_hub):
            if neighbor == to_hub:
                return cap
        return 0

    def move_drone(self, drone: Drone, to_hub: Hub) -> bool:
        """
        Attempt to move a drone to a new hub.
        Returns True if move was successful, False otherwise.
        """
        if drone.state == "delivered":
            return False

        # Check if destination is reachable
        neighbors = [n for n, _ in self.graph.get_neighbors(drone.hub)]
        if to_hub not in neighbors:
            return False

        # Check if zone is blocked
        if to_hub.zone == Zone.BLOCKED:
            return False

        # Handle restricted zones (2-turn movement)
        if to_hub.zone == Zone.RESTRICTED:
            # First turn: enter transit
            if drone.state != "in_transit":
                drone.state = "in_transit"
                self.in_transit[drone] = (drone.hub, to_hub)
                # Remove from current hub
                if drone in drone.hub.drones:
                    drone.hub.drones.remove(drone)
                return True
            else:
                return False

        # Check capacity
        if not self.can_move_to_hub(to_hub):
            return False

        # Execute move
        if drone in drone.hub.drones:
            drone.hub.drones.remove(drone)

        drone.hub = to_hub
        to_hub.drones.append(drone)

        # Check if reached goal
        if to_hub == self.end_hub:
            drone.state = "delivered"
        else:
            drone.state = "waiting"

        return True

    def process_transit_drones(self) -> list[str]:
        """Process drones in transit to restricted zones.
        Returns movement strings.
        """
        moves = []
        completed_transits = []

        for drone, (from_hub, to_hub) in self.in_transit.items():
            # Check if destination has capacity
            if self.can_move_to_hub(to_hub):
                # Complete the transit
                drone.hub = to_hub
                to_hub.drones.append(drone)

                if to_hub == self.end_hub:
                    drone.state = "delivered"
                else:
                    drone.state = "waiting"

                completed_transits.append(drone)
                moves.append(f"D{drone.id}-{to_hub.name}")
            # If no capacity, drone stays in transit (shouldn't happen with
            # proper planning)

        # Remove completed transits
        for drone in completed_transits:
            del self.in_transit[drone]

        return moves

    def simulate_turn(self, moves: dict[Drone, Hub]) -> str:
        """
        Execute one turn of simulation with planned moves.
        moves: dict mapping drones to their target hubs
        Returns: formatted output string for this turn
        """
        turn_output = []

        # First, handle drones entering transit to restricted zones
        transit_moves = []
        regular_moves = []

        for drone, target in moves.items():
            if drone.state == "delivered":
                continue

            if target.zone == Zone.RESTRICTED and drone.state != "in_transit":
                transit_moves.append((drone, target))
            else:
                regular_moves.append((drone, target))

        # Process transit entries first
        for drone, target in transit_moves:
            if self.move_drone(drone, target):
                from_hub, to_hub = self.in_transit[drone]
                turn_output.append(
                    f"D{drone.id}-{from_hub.name}-{to_hub.name}"
                )

        # Process regular moves
        for drone, target in regular_moves:
            if self.move_drone(drone, target):
                turn_output.append(f"D{drone.id}-{target.name}")

        # Process drones completing their transit
        completed = self.process_transit_drones()
        turn_output.extend(completed)

        self.turn += 1
        output = " ".join(sorted(turn_output))
        if output:  # Only add non-empty turns
            self.movements.append(output)

        return output

    def is_complete(self) -> bool:
        """Check if all drones have reached the goal"""
        return all(d.state == "delivered" for d in self.drones)

    def get_output(self) -> str:
        """Get the full simulation output"""
        return "\n".join(self.movements)

    def print_state(self):
        """Debug: print current state"""
        print(f"\n=== Turn {self.turn} ===")
        for hub in self.graph.adj_lst.keys():
            drones_here = [
                d.id
                for d in self.drones
                if d.hub == hub and d.state != "in_transit"
            ]
            if drones_here:
                print(f"{hub.name}: {drones_here}")

        if self.in_transit:
            print("In transit:")
            for drone, (from_h, to_h) in self.in_transit.items():
                print(f"  D{drone.id}: {from_h.name} -> {to_h.name}")
