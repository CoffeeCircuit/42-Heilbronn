# MazeGen Library

A Python library for procedural maze generation with multiple algorithms.

## Installation

```bash
pip install mazegen-1.0.0-py3-none-any.whl
```

## Quick Start

```python
from mazegen import MazeGenerator

# Create and configure
maze = MazeGenerator()
maze.width = 25
maze.height = 20
maze.entry = (0, 0)      # (x, y) coordinates
maze.exit = (19, 24)
maze.perfect = True
maze.seed = 42           # Optional: for reproducibility
maze.algorithm = "dfs"   # or "hak"

# Generate
maze.generate()

# Access the grid
grid = maze.grid  # 2D list of integers (wall bit flags)

# Write to file
maze.output = "output.txt"
maze.write()
```

## Loading from Configuration

```python
from mazegen import MazeGenerator

maze = MazeGenerator()
maze.read("config.txt")  # Loads all parameters
maze.generate()
maze.write()
```

## Grid Format

Each cell is an integer with bit flags for walls:
- Bit 0 (0x1): North wall
- Bit 1 (0x2): East wall  
- Bit 2 (0x4): South wall
- Bit 3 (0x8): West wall

Example: `9` (binary 1001) = North + West walls closed

## Accessing Maze Data

```python
# Get grid dimensions
width = maze.width
height = maze.height

# Check specific cell walls
cell_value = grid[row][col]
has_north_wall = bool(cell_value & 0x1)
has_east_wall = bool(cell_value & 0x2)
has_south_wall = bool(cell_value & 0x4)
has_west_wall = bool(cell_value & 0x8)
```

## Available Algorithms

### DFS (Depth-First Search)
```python
maze.algorithm = "dfs"
```
Creates long, winding corridors. Fast and memory-efficient.

### Hunt-and-Kill
```python
maze.algorithm = "hak"
```
Creates more uniform passage distribution with shorter dead ends.

## Perfect vs Imperfect Mazes

```python
# Perfect: single path between any two points
maze.perfect = True

# Imperfect: multiple paths, contains loops
maze.perfect = False
```

## Reproducibility

Use seeds for deterministic generation:

```python
maze.seed = 42
maze.generate()  # Same maze every time with this seed
```

## API Reference

### MazeGenerator Class

**Attributes:**
- `width: int | None` - Maze width in cells
- `height: int | None` - Maze height in cells
- `entry: tuple[int, int] | None` - Entry position (x, y)
- `exit: tuple[int, int] | None` - Exit position (x, y)
- `grid: list[list[int]] | None` - 2D grid with wall bit flags
- `output: str | PathLike | None` - Output file path
- `perfect: bool | None` - Perfect maze flag
- `seed: int | None` - Random seed
- `algorithm: str | None` - Algorithm choice ("dfs" or "hak")

**Methods:**
- `read(file)` - Load configuration from file
- `generate()` - Generate maze using selected algorithm
- `write()` - Write maze to output file
- `reset()` - Reset grid to all walls

## Other Exports

```python
from mazegen import (
    MazeGenerator,    # Main generator class
    Visualizer,       # Terminal visualizer
    Graphics,         # ANSI color utilities
    dfs,              # DFS algorithm function
    hak,              # Hunt-and-Kill algorithm function
    make_imperfect,   # Add loops to perfect maze
    make_p42_mask,    # Create "42" pattern mask
)
```

## Requirements

- Python 3.10 or later
- No external dependencies

## License

Part of the 42 curriculum project.
