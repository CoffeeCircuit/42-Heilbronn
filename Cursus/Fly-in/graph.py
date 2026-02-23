from enum import Enum, auto


class Zone(Enum):
    NORMAL = auto()
    BLOCKED = auto()
    RESTRICTED = auto()
    PRIORITY = auto()


class Drone:
    def __init__(self, id: int, x: int, y: int) -> None:
        self.id = id
        self.x = x
        self.y = y


class Hub:
    def __init__(
        self,
        name: str,
        x: int,
        y: int,
        zone: Zone = Zone.NORMAL,
        color: str | None = None,
        max_drones: int = 1,
    ) -> None:
        self.name = name
        self.x = x
        self.y = y
        self.zone = zone
        self.color = color
        self.max_drones = max_drones
        self.drones: list[Drone] = []

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Hub):
            return NotImplemented
        return all(
            (
                self.x == other.x,
                self.y == other.y,
                self.zone == other.zone,
                self.max_drones == other.max_drones,
            )
        )

    def __hash__(self) -> int:
        return hash((self.x, self.y, self.zone, self.max_drones))

    def __str__(self) -> str:
        return f"{self.name}"


class Graph:
    """
    Graph data stucture represented by an adjacency list
    """

    def __init__(self) -> None:
        self.nb_drones: int = 0
        self.graph: dict[Hub, list[tuple[Hub, int]]] = {}

    def add_hub(self, hub: Hub):
        if not isinstance(hub, Hub):
            raise TypeError(
                f"'{type(hub).__name__}' not of type '{Hub.__name__}'"
            )
        if hub in self.graph:
            raise KeyError(f"Duplicate hub definition: '{hub}'")
        elif hub.name in {k.name for k in self.graph.keys()}:
            raise ValueError(f"Hub name '{hub.name}' already allocated")
        self.graph[hub] = []

    def add_connection(self, from_: Hub, to_: Hub, cap: int = 1):
        connections = self.graph.get(from_)
        if connections is None:
            raise KeyError(f"Undefined hub: '{from_}'")
        if to_ in connections:
            raise ValueError(
                f"Duplicate connection definition: '{from_}' -> '{to_}'"
            )
        if to_ in self.graph and from_ in self.graph[to_]:
            raise ValueError(
                (
                    f"Duplicate connection: '{from_}' -> '{to_}'"
                    f" with '{to_}' -> '{from_}'"
                )
            )
        self.graph[from_].append((to_, cap))

    def __iter__(self):
        for k in self.graph:
            yield k

    def __str__(self) -> str:
        if not len(self.graph):
            return "{}"

        from io import StringIO

        buf = StringIO()
        buf.write("{\n")
        outer_i = 0
        for k, list_v in self.graph.items():
            buf.write(f"    {str(k)}: ")
            if not len(list_v):
                buf.write("[]")
                buf.write(",\n" if outer_i < len(self.graph) - 1 else "\n")
            elif len(list_v) == 1:
                buf.write(f"[({str(list_v[0][0])}, {list_v[0][1]})]")
                buf.write(",\n" if outer_i < len(self.graph) - 1 else "\n")
            else:
                buf.write("[\n")
                for inner_i, v in enumerate(list_v):
                    buf.write(f"        ({str(v[0])}, {v[1]})")
                    if inner_i < len(list_v) - 1:
                        buf.write(",\n")
                    else:
                        buf.write("\n")
                buf.write("    ]")
                buf.write(",\n" if outer_i < len(self.graph) - 1 else "\n")
            outer_i += 1
        buf.write("}\n")

        return buf.getvalue()


# TODO

# Hub Hash/Equality Consistency
#   You hash on (x, y, zone, max_drones) but do not include name or color. If
#   two hubs have the same coordinates, zone, and max_drones but different
#   names/colors, they will be considered equal and duplicate.
#   Is this intended? If not, include all relevant immutable properties in
#   both __eq__ and __hash__.

# Mutable Properties in Hash
#   You do not include drones (a list) in the hash, which is correct. Including
#   mutable types would break hashing.

# Error Handling
#   You raise KeyError for duplicate hubs, but the message is a string, so
#   Python wraps it in quotes. Consider using ValueError for custom messages,
#   or raise KeyError with the actual duplicate key.

# Hub Name Uniqueness
#   You check for duplicate names separately from the hash/equality check. This
#   is good, but if you want name uniqueness to be primary, consider hashing on
#   name.

# Graph Connections
#   The check for undirectional edges is good, but it only prevents adding the
#   reverse edge if the forward edge exists. If you want true undirected graphs
#   you may want to store connections in both directions.

# String Representation
#   The __str__ method is well-structured, but the inner and outer loop index
#   reuse can cause formatting bugs (which you already fixed).

# Zone Enum
#   You use auto() for enum values, which is fine, but if you need string vals
#   for serialization, consider using str or explicit values.

# Type Checking
#   You check isinstance(hub, Hub) in add_hub, which is good for robustness.

# No Removal Methods
#   There are no methods for removing hubs or connections. If you need
#   mutability, consider adding them.

# No Validation for Connection Existence
#   In add_connection, you check if from_ exists, but not if to_ exists in the
#   graph. You do check for reverse connections, which is good.

# No Support for Metadata on Connections
#   If you want to support metadata (e.g., weights, capacities), you’ll need to
#   extend your connection storage.

# No Handling for Edge Cases
#   If the graph is empty, __str__ returns {}, which is fine.

# No Docstrings for Methods
#   Adding docstrings for methods would improve maintainability.

# No Validation for Hub Properties
#   You do not validate that max_drones is positive, or that name is valid (no
#   spaces/dashes).

# No Iteration Over Connections
#   You only iterate over hubs, not connections. If you need to traverse edges,
#   consider adding a method.
