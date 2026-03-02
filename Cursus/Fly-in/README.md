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
# Clone the repository
git clone <repository-url>
cd Fly-in

# No external dependencies required (uses Python standard library + tkinter)
# Ensure Python 3.10+ is installed
python3 --version
```

### Usage

#### Basic Execution

```bash
# Run simulation on a map file
python3 flyin.py <path-to-map-file>

# Example
python3 flyin.py maps/easy/01_linear_path.txt
```

#### Visual Mode

```bash
# Enable colored terminal output and GUI visualization
python3 flyin.py maps/easy/02_simple_fork.txt --visual
# or
python3 flyin.py maps/medium/01_dead_end_trap.txt -v
```

#### Debug Mode

```bash
# Enable debug logging
python3 flyin.py maps/hard/01_maze_nightmare.txt --debug -v
```

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
- **Medium maps**: 10-30 turns
- **Hard maps**: ≤60 turns
- **Challenger map**: Aim for <41 turns (optional, advanced)

## Project Structure

```
Fly-in/
├── flyin.py          # Main entry point
├── parser.py         # Map file parsing with error handling
├── graph.py          # Graph structure, Dijkstra, k-shortest paths
├── scheduler.py      # Path planning (max-flow) and turn scheduling
├── simulation.py     # Turn-by-turn simulation engine
├── visualizer.py     # Tkinter GUI with animation
├── colors.py         # ANSI and hex color definitions
├── config.py         # GUI configuration settings
└── maps/             # Test maps by difficulty
    ├── easy/
    ├── medium/
    ├── hard/
    └── challenger/
```

## Algorithm Details

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

---

**Author**: Andrei Balcu (abalcu)  
**Institution**: 42 Heilbronn  
**License**: Educational Project

