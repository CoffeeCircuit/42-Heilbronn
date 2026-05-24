import math
import random
import pygame
from collections import deque

from . import constants as const
from .maze import Maze


REVERSE = {
    (-1, 0): (1, 0),
    (1, 0): (-1, 0),
    (0, -1): (0, 1),
    (0, 1): (0, -1),
}


class Ghost:
    def __init__(
        self,
        maze: Maze,
        row: int,
        col: int,
        color: tuple[int, int, int],
        scatter_goal: tuple[int, int] = (0, 0),
    ) -> None:
        self.maze = maze
        self.color = color
        self.scatter_goal = scatter_goal
        self._base_speed: float = (
            const.GHOST_SPEED * const.TILE_SIZE
        )
        self.speed: float = self._base_speed
        self._home: tuple[int, int] = (row, col)

        self.grid_row = row
        self.grid_col = col
        self.px: float = col * const.TILE_SIZE
        self.py: float = row * const.TILE_SIZE

        self.direction: tuple[int, int] | None = None
        self.goal: tuple[int, int] = scatter_goal
        self.mode: str = "scatter"

    def set_base_speed(self, speed: float) -> None:
        self._base_speed = speed

    def set_goal(self, row: int, col: int) -> None:
        self.goal = (row, col)

    def start_freight(self) -> None:
        self.mode = "freight"
        self.speed = self._base_speed * const.FREIGHT_SPEED_MULT
        self.direction = None

    def start_spawn(self) -> None:
        self.mode = "spawn"
        self.speed = self._base_speed * const.SPAWN_SPEED_MULT
        self.goal = self._home
        self.direction = None

    def go_idle(self) -> None:
        self.mode = "idle"
        self.speed = 0.0

    def go_normal(self, main_mode: str) -> None:
        self.mode = main_mode
        self.speed = self._base_speed

    def _get_walkable_directions(
        self, exclude_reverse: bool = True
    ) -> list[tuple[int, int]]:
        reverse = (
            REVERSE.get(self.direction)
            if exclude_reverse and self.direction
            else None
        )
        dirs: list[tuple[int, int]] = []
        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            if (dr, dc) == reverse:
                continue
            if self.maze.is_walkable(
                self.grid_row + dr, self.grid_col + dc
            ):
                dirs.append((dr, dc))
        return dirs

    def _choose_random_direction(
        self,
    ) -> tuple[int, int] | None:
        options = self._get_walkable_directions()
        if not options:
            options = self._get_walkable_directions(
                exclude_reverse=False
            )
        if not options:
            return None
        return random.choice(options)

    def _bfs_distance(
        self, sr: int, sc: int
    ) -> float | int:
        if (sr, sc) == self.goal:
            return 0
        rows = len(self.maze.out)
        cols = len(self.maze.out[0])
        visited: set[tuple[int, int]] = {(sr, sc)}
        queue: deque[tuple[int, int, int]] = deque(
            [(sr, sc, 0)]
        )
        while queue:
            r, c, d = queue.popleft()
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                if (nr, nc) in visited:
                    continue
                if not (0 <= nr < rows and 0 <= nc < cols):
                    continue
                if not self.maze.is_walkable(nr, nc):
                    continue
                if (nr, nc) == self.goal:
                    return d + 1
                visited.add((nr, nc))
                queue.append((nr, nc, d + 1))
        return float("inf")

    def _choose_direction(self) -> tuple[int, int] | None:
        if self.mode == "idle":
            return None
        if self.mode == "freight":
            return self._choose_random_direction()
        options = self._get_walkable_directions()
        if not options:
            options = self._get_walkable_directions(
                exclude_reverse=False
            )
        if not options:
            return None
        if len(options) == 1:
            return options[0]
        best = None
        best_dist = float("inf")
        for dr, dc in options:
            nr = self.grid_row + dr
            nc = self.grid_col + dc
            if self.mode == "spawn":
                dist = self._bfs_distance(nr, nc)
            else:
                dist = math.hypot(
                    nr - self.goal[0], nc - self.goal[1]
                )
            if dist < best_dist:
                best_dist = dist
                best = (dr, dc)
        return best

    def update(self, dt: float) -> None:
        if self.mode == "idle":
            return

        if not self.direction:
            self.direction = self._choose_direction()
            if not self.direction:
                return

        move = self.speed * dt
        dr, dc = self.direction
        target_px = (self.grid_col + dc) * const.TILE_SIZE
        target_py = (self.grid_row + dr) * const.TILE_SIZE
        dx = target_px - self.px
        dy = target_py - self.py
        dist = (dx * dx + dy * dy) ** 0.5

        if dist <= move:
            self.px = target_px
            self.py = target_py
            self.grid_row += dr
            self.grid_col += dc
            if (
                self.mode == "spawn"
                and (self.grid_row, self.grid_col)
                == self._home
            ):
                self.direction = None
            else:
                self.direction = self._choose_direction()
        else:
            self.px += (dx / dist) * move
            self.py += (dy / dist) * move

    def reset(self, row: int, col: int) -> None:
        self._home = (row, col)
        self.grid_row = row
        self.grid_col = col
        self.px = col * const.TILE_SIZE
        self.py = row * const.TILE_SIZE
        self.direction = None
        self.mode = "scatter"
        self.speed = self._base_speed

    def draw(
        self, screen: pygame.SurfaceType, offset_y: int = 0
    ) -> None:
        half = const.TILE_SIZE // 2
        cx = int(self.px) + half
        cy = int(self.py) + half + offset_y
        if self.mode == "freight":
            pygame.draw.circle(
                screen, const.COLOR_BLUE, (cx, cy), half - 2
            )
        elif self.mode in ("spawn", "idle"):
            pygame.draw.circle(
                screen, const.COLOR_GREY, (cx, cy), half // 2
            )
        else:
            pygame.draw.circle(
                screen, self.color, (cx, cy), half - 2
            )
