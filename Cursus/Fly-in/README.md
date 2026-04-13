*This project has been created as part of the 42 curriculum by abalcu*

# Fly-in: Drone Routing Simulator

## Description

Fly-in is an advanced drone routing and pathfinding simulator that optimizes multi-drone navigation through complex network topologies. The system parses map files, plans optimal paths using graph algorithms, and simulates turn-by-turn drone movements while respecting zone capacities, connection constraints, and movement costs.

### Key Features

- **Multi-drone path planning**: Uses k-shortest paths with max-flow algorithms to distribute drones efficiently across multiple routes
- **Zone-aware pathfinding**: Handles different zone types (normal, restricted, priority, blocked) with varying movement costs
- **Capacity management**: Enforces both zone capacity (max_drones) and connection capacity (max_link_capacity) constraints
- **Turn-based simulation**: Discrete turn system with conflict resolution and strategic waiting
- **Visual output**: 
  - Colored terminal output for movement tracking
  - Interactive Tkinter GUI with pan/zoom, animation controls, and tooltips
- **Performance optimization**: Targets specific turn counts for different difficulty levels

### Zone Types

- **Normal**: Standard traversal (1 turn)
- **Restricted**: Requires 2 turns to traverse (drone in transit)
- **Priority**: Preferred routes (0.5 cost in pathfinding)
- **Blocked**: Inaccessible zones

## Instructions

### Installation

```bash
# Install dependencies using uv (recommended)
make install

# Or manually with uv
uv sync --python 3.10

# Ensure Python 3.10+ is installed
python3 --version
```

### Usage

#### Basic Execution

```bash
# Run simulation on a map file using make
make run ARGS="maps/easy/01_linear_path.txt"

# Or run directly with uv
uv run flyin.py maps/easy/01_linear_path.txt

# Or with standard python
python3 flyin.py maps/easy/01_linear_path.txt
```

#### Visual Mode

```bash
# Enable colored terminal output and GUI visualization
make run ARGS="maps/easy/02_simple_fork.txt --visual"

# Or directly
uv run flyin.py maps/medium/01_dead_end_trap.txt -v
```

#### Debug Mode

```bash
# Enable debug logging with make
make debug ARGS="maps/hard/01_maze_nightmare.txt --debug -v"

# Or run directly
uv run python3 -m pdb flyin.py maps/hard/01_maze_nightmare.txt
```

#### Benchmark Mode

Run all test maps and compare against performance targets:

```bash
make benchmark
```

This will execute all maps and display:
- Steps taken for each map
- Whether it meets the target performance
- Summary of passed/failed tests

### Map File Format

Map files use a simple key-value syntax:

```
nb_drones: 3

start_hub: start 0 0 [color=green]
hub: junction 1 0 [color=yellow max_drones=2]
hub: waypoint 2 0 [zone=priority color=cyan]
end_hub: goal 3 0 [color=red max_drones=5]

connection: start-junction
connection: junction-waypoint [max_link_capacity=2]
connection: waypoint-goal
```

**Zone metadata**: `[zone=<type> color=<name> max_drones=<int>]`
- Valid zone types: `normal`, `blocked`, `restricted`, `priority`
- Colors: `green`, `blue`, `yellow`, `orange`, `red`, `purple`, `cyan`, `rainbow`, etc.
- Default `max_drones`: 1

**Connection metadata**: `[max_link_capacity=<int>]`
- Limits simultaneous drone traversal
- Default: 1

### GUI Controls

- **Mouse drag**: Pan the graph view
- **Scroll wheel**: Zoom in/out
- **Restart**: Reset animation to beginning
- **Prev**: Go to previous turn
- **Pause**: Pause animation
- **Play**: Auto-play animation
- **Next**: Advance to next turn
- **Hover over nodes**: Show hub information tooltip

### Performance Targets

- **Easy maps**: ≤10 turns
  - `01_linear_path.txt`: Target ≤6 turns
  - `02_simple_fork.txt`: Target ≤6 turns
  - `03_basic_capacity.txt`: Target ≤8 turns
- **Medium maps**: 10-30 turns
  - `01_dead_end_trap.txt`: Target ≤15 turns
  - `02_circular_loop.txt`: Target ≤20 turns
  - `03_priority_puzzle.txt`: Target ≤12 turns
- **Hard maps**: ≤60 turns
  - `01_maze_nightmare.txt`: Target ≤45 turns
  - `02_capacity_hell.txt`: Target ≤60 turns
  - `03_ultimate_challenge.txt`: Target ≤35 turns
- **Challenger map**: Aim for ≤41 turns (optional, advanced)
  - `01_the_impossible_dream.txt`: Reference record: 41 turns

## Project Structure

```
Fly-in/
├── flyin.py          # Main entry point and argument parsing
├── parser.py         # Map file parsing with error handling
├── graph.py          # Graph structure, Dijkstra, k-shortest paths
├── scheduler.py      # Path planning (max-flow) and turn scheduling
├── simulation.py     # Turn-by-turn simulation engine
├── visualizer.py     # Tkinter GUI with animation and controls
├── colors.py         # ANSI and hex color definitions
├── config.py         # GUI configuration settings
├── Makefile          # Build, run, lint, and benchmark commands
├── pyproject.toml    # Python project configuration
├── uv.lock           # Dependency lock file
├── __init__.py       # Package initialization
└── maps/             # Test maps by difficulty
    ├── README.md
    ├── easy/
    │   ├── 01_linear_path.txt
    │   ├── 02_simple_fork.txt
    │   └── 03_basic_capacity.txt
    ├── medium/
    │   ├── 01_dead_end_trap.txt
    │   ├── 02_circular_loop.txt
    │   └── 03_priority_puzzle.txt
    ├── hard/
    │   ├── 01_maze_nightmare.txt
    │   ├── 02_capacity_hell.txt
    │   └── 03_ultimate_challenge.txt
    └── challenger/
        └── 01_the_impossible_dream.txt
```

## Makefile Commands

The project includes a comprehensive Makefile for common tasks:

### Development Commands

```bash
make install       # Install dependencies using uv with Python 3.10
make run          # Run simulation (use ARGS="path/to/map.txt")
make debug        # Run with Python debugger (pdb)
make clean        # Remove cache files and virtual environments
```

### Code Quality

```bash
make lint         # Run flake8 and mypy with standard checks
make lint-strict  # Run strict type checking with mypy
```

### Testing

```bash
make benchmark    # Run all test maps and compare against targets
```

The benchmark command tests all maps and displays:
- ✅ Pass/Fail status for each map based on target turns
- Total tests passed vs. failed
- Performance comparison (if exceeded, by how many turns)

## Algorithm Explanation

### Pathfinding Strategy

Fly-in uses a sophisticated two-phase approach to optimize multi-drone routing:

#### Phase 1: Path Discovery via K-Shortest Paths
The system generates up to **k=5 candidate paths** from source to destination using a modified Dijkstra algorithm with path enumeration. This provides multiple disjoint and diverse routes rather than relying on a single optimal path, enabling parallel drone movement and better congestion management.

**Cost Calculation:**
- **Normal zones**: 1.0 unit cost
- **Restricted zones**: 2.0 unit cost (requires transit through midpoint)
- **Priority zones**: 0.5 unit cost (encouraged routes)
- **Blocked zones**: Infinite cost (impassable)

#### Phase 2: Optimal Drone Assignment via Max-Flow
Once candidate paths are identified, drones are assigned to paths using the **Edmonds-Karp algorithm** (BFS-based maximum flow):

1. **Flow network construction**: Create a flow network where:
   - Source connects to each path with capacity = min(total_drones, path_bottleneck)
   - Each path connects to sink with capacity = path_bottleneck (minimum edge capacity)

2. **Flow computation**: Edmonds-Karp finds augmenting paths using BFS and computes maximum flow, ensuring drones are distributed across paths proportional to their capacities

3. **Bottleneck capacity**: Each path's capacity is determined by its minimum edge capacity (the "weakest link")

### Constraint Handling

**Hub Capacity (max_drones)**
- Each hub has a maximum occupancy limit (default: 1)
- Drones queue outside hubs rather than violate constraints
- Strategic waiting prevents capacity violations

**Connection Capacity (max_link_capacity)**
- Each edge has a maximum concurrent traversal limit
- Enforced at the flow assignment phase via bottleneck calculation
- Prevents congestion on critical network connections

**Restricted Zone Transit**
- Drones entering restricted zones enter a "transit" state
- They occupy a midpoint for one full turn before arriving at destination
- Ensures proper 2-turn traversal without double-counting positions

### Turn-Based Scheduling & Conflict Resolution

Each turn executes in this order:

1. **Move planning**: Determine which drones move and where (respecting all constraints)
2. **Transit processing**: Complete any in-transit drones moving through restricted zones
3. **Capacity validation**: Verify no capacity violations after moves
4. **Strategic waiting**: Drones unable to move remain in current hub, queuing for next turn

This greedy approach with lookahead ensures deadlock-free routing while minimizing total turns.

### Design Rationale

| Decision | Rationale |
|----------|-----------|
| K-shortest paths | Avoids single-path bottlenecks; enables parallel routing |
| Edmonds-Karp algorithm | Polynomial-time guarantee; practical for network constraints |
| Bottleneck capacity | Respects edge constraints; prevents overloading links |
| Greedy turn-by-turn execution | Distributes drones effectively while maintaining feasibility |
| Strategic waiting | Resolves conflicts without complex backtracking |



### Pathfinding

1. **K-shortest paths** (Yen's algorithm): Find multiple diverse routes
2. **Max-flow assignment** (Edmonds-Karp): Distribute drones optimally across paths based on bottleneck capacities
3. **Zone-aware costs**: Priority zones preferred, restricted zones penalized

### Scheduling

- **Connection capacity tracking**: Prevents multiple drones from violating link capacity per turn
- **Hub capacity enforcement**: Respects max_drones limits
- **Conflict resolution**: Drones wait when movement blocked
- **Restricted zone handling**: 2-turn movement with in-transit state

## Resources

### Algorithms

- [Dijkstra's Algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) - Shortest path finding
- [Yen's K-Shortest Paths](https://en.wikipedia.org/wiki/Yen%27s_algorithm) - Finding multiple alternative paths
- [Edmonds-Karp Algorithm](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm) - Maximum flow computation
- [Graph Theory](https://en.wikipedia.org/wiki/Graph_theory) - Fundamental concepts

### Python Libraries

- [tkinter](https://docs.python.org/3/library/tkinter.html) - GUI framework
- [heapq](https://docs.python.org/3/library/heapq.html) - Priority queue for Dijkstra
- [enum](https://docs.python.org/3/library/enum.html) - Zone type definitions
- [argparse](https://docs.python.org/3/library/argparse.html) - CLI argument parsing

### Design Patterns

- **Strategy Pattern**: Different zone types with varying costs
- **Observer Pattern**: Animation tracking and state updates
- **Builder Pattern**: Graph construction from tokens

### Related Concepts

- Multi-agent pathfinding (MAPF)
- Network flow optimization
- Constraint satisfaction problems (CSP)
- Turn-based simulation systems
