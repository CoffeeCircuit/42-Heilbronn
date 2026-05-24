import pygame

from . import constants as const
from .maze import Maze


class Pacgums:
    def __init__(self, maze: Maze, exclude: set[tuple[int, int]]) -> None:
        self.pacgums: dict[tuple[int, int], str] = {}
        self._blink_timer: float = 0.0
        self._blink_visible: bool = True
        rows = len(maze.out)
        cols = len(maze.out[0])
        for r in range(1, rows, 2):
            for c in range(1, cols, 2):
                if (r, c) in exclude:
                    continue
                if maze.out[r][c] is None and self._has_exit(maze, r, c):
                    self.pacgums[(r, c)] = "pacgum"
        self._place_super(maze)

    def _has_exit(self, maze: Maze, r: int, c: int) -> bool:
        return any(
            maze.is_walkable(r + dr, c + dc)
            for dr, dc in ((-1, 0), (1, 0), (0, -1), (0, 1))
        )

    def _place_super(self, maze: Maze) -> None:
        corners = [
            (1, 1),
            (1, len(maze.out[0]) - 2),
            (len(maze.out) - 2, 1),
            (len(maze.out) - 2, len(maze.out[0]) - 2),
        ]
        for cr, cc in corners:
            pos = self._bfs_walkable(maze, cr | 1, cc | 1)
            if pos and pos in self.pacgums:
                self.pacgums[pos] = "super"

    def _bfs_walkable(
        self, maze: Maze, sr: int, sc: int
    ) -> tuple[int, int] | None:
        rows = len(maze.out)
        cols = len(maze.out[0])
        visited: set[tuple[int, int]] = set()
        queue: list[tuple[int, int]] = [(sr, sc)]
        while queue:
            r, c = queue.pop(0)
            if (r, c) in visited:
                continue
            visited.add((r, c))
            if r % 2 == 1 and c % 2 == 1 and maze.out[r][c] is None:
                if self._has_exit(maze, r, c):
                    return (r, c)
            for dr, dc in ((-2, 0), (2, 0), (0, -2), (0, 2)):
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols:
                    if (nr, nc) not in visited:
                        queue.append((nr, nc))
        return None

    def eat(self, row: int, col: int) -> str | None:
        return self.pacgums.pop((row, col), None)

    @property
    def remaining(self) -> int:
        return len(self.pacgums)

    def update(self, dt: float) -> None:
        self._blink_timer += dt
        if self._blink_timer >= 0.2:
            self._blink_timer = 0.0
            self._blink_visible = not self._blink_visible

    def draw(self, screen: pygame.SurfaceType, offset_y: int = 0) -> None:
        half = const.TILE_SIZE // 2
        for (r, c), kind in self.pacgums.items():
            cx = c * const.TILE_SIZE + half
            cy = r * const.TILE_SIZE + half + offset_y
            if kind == "super":
                if self._blink_visible:
                    pygame.draw.circle(screen, (255, 255, 255), (cx, cy), 8)
            else:
                pygame.draw.circle(screen, (255, 255, 255), (cx, cy), 3)
