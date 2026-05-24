*This project has been created as part of the 42 curriculum by ksmailov, abalcu*

# Pac-Man

## Description

A Pac-Man clone built in Python with Pygame. Features procedurally generated mazes, 4 ghosts with scatter/chase/freight/spawn/idle modes, BFS pathfinding, level timer, 10-level progression with increasing difficulty, screen-based state machine (title, pause, game over, victory, name entry), and persistent highscore system.

## Instructions

```bash
make install     # install dependencies
make run         # run the game
make lint        # flake8 + mypy
make debug       # run with pdb
make clean       # remove caches
```

Or directly: `python3 pac-man.py config.json`

### Packaging for Itch.io

```bash
make build
python3 -m http.server 8000 --directory build/web
```

## Resources

- [Pacmancode](https://pacmancode.com/) — Pac-Man game development tutorial

## Configuration

JSON config file with `#` and `//` comment support. Missing keys use defaults, invalid values are clamped, unknown keys ignored.

| Key | Default | Description |
|-----|---------|-------------|
| `highscore_filename` | `"highscore.json"` | Highscore file path |
| `width` | `14` | Maze width (min 5) |
| `height` | `18` | Maze height (min 5) |
| `lives` | `3` | Starting lives (min 1) |
| `points_per_pacgum` | `10` | Points per pacgum (min 1) |
| `points_per_super_pacgum` | `50` | Points per super-pacgum (min 1) |
| `seed` | `42` | Base seed for level 1 |
| `level_max_time` | `90` | Seconds per level (min 10) |

## Highscore

Persistent JSON storage — top 10 entries sorted by score. Player names: max 10 chars, alphanumeric + spaces. Displayed on title screen (top 3 preview) and dedicated highscores screen (full top 10). Name entry after game over or victory.

## Maze Generation

Uses the `mazegenerator` package (A-Maze-ing, `PERFECT=False`). The `out` grid uses odd-odd indices for cell centers and even indices for walls/passages. BFS finds the nearest reachable cell for player spawn (`maze.center`) and ghost spawns (4 corners via `maze.nearest_cell`).

## Implementation

### Modules

- **`config.py`** — Pydantic-validated JSON config with comment stripping and value clamping
- **`maze.py`** — Maze generation, pre-rendered surface, `is_walkable()`, `nearest_cell()` (BFS), `center` property
- **`player.py`** — Grid movement with direction queuing, sprite rotation, smooth interpolation
- **`ghost.py`** — 4 ghosts with goal-based AI (Euclidean for scatter/chase, BFS for spawn), no-U-turn rule, 5 modes (scatter/chase/freight/spawn/idle), per-ghost scatter corners, level-based speed scaling
- **`pacgums.py`** — Placement on corridors, super-pacgums via BFS from 4 corners, blink animation
- **`game.py`** — Gameplay logic: score, lives, level timer, ghost collision, freight/spawn/idle management, mode timer, level progression with 10-level cap
- **`screens.py`** — Screen ABC + 8 screen classes (title, waiting, pause, game over, victory, name entry, highscores, instructions)
- **`pacman.py`** — App class routes events/updates/draws to current screen
- **`highscore.py`** — Load/save JSON, top 10, name validation, error resilience
- **`font.py`** / **`sprites.py`** — PressStart2P font rendering, spritesheet loader

### Key decisions

- **Screen pattern**: `Screen` ABC with `handle_event()`/`update()` returning `str | None` for state transitions. `App` class acts as router.
- **Ghost AI**: Scatter (7s, corner) / chase (20s, Pac-Man) alternates on global timer. Freight: slow + random. Spawn: fast + BFS home. Idle: wait for freight expiry.
- **Level progression**: 10 levels, each with `seed + level - 1`. Ghost speed +0.5/level, freight time -0.5s/level (min 2s). Timer expires = game over.
- **Movement**: Grid-based with direction queue. Continuous until wall hit. Collision is tile-based.

## General Software Architecture

```
pac-man.py                  → entry point
src/pac_man/
├── __init__.py              → package init, main()
├── config.py                → ConfigData (pydantic) + Config
├── constants.py             → tile size, speeds, colors, states
├── font.py                  → Text (PressStart2P)
├── game.py                  → Game (gameplay state + logic)
├── ghost.py                 → Ghost AI, 5 modes, BFS pathfinding
├── highscore.py             → Highscore load/save/validate
├── maze.py                  → Maze generation + rendering
├── pacgums.py               → Pacgum placement + drawing
├── pacman.py                → App (screen router) + main loop
├── player.py                → Player movement + animation
├── screens.py               → Screen ABC + 8 UI screens
└── sprites.py               → Spritesheet loader
```

### Class relationships

- `App` owns `Config`, `Highscore`, current `Screen`, and `Game`
- `App` routes events/updates/draws to the active `Screen` subclass
- `Game` owns `Maze`, `Player`, 4 `Ghost` instances, `Pacgums`
- `Player`/`Ghost` reference `Maze` for `is_walkable()`
- `Highscore` is standalone, used by `NameEntryScreen` and `TitleScreen`

## Project Management

Project management documents are in the `docs/` directory.
