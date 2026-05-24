import pygame

from . import constants as const
from .maze import Maze
from .sprites import Spritesheet

DIRECTIONS = {
    "up": (-1, 0),
    "down": (1, 0),
    "left": (0, -1),
    "right": (0, 1),
}


class Player:
    def __init__(self, maze: Maze) -> None:
        self.maze = maze
        self.speed: float = const.PACMAN_SPEED * const.TILE_SIZE

        row, col = maze.center
        self.grid_row = row
        self.grid_col = col
        self.px: float = col * const.TILE_SIZE
        self.py: float = row * const.TILE_SIZE

        self.direction: tuple[int, int] | None = None
        self.next_direction: tuple[int, int] | None = None

        spritesheet = Spritesheet()
        base = [spritesheet.getImage(0, i * 32) for i in range(3)]
        self.frames: dict[str, list[pygame.SurfaceType]] = {
            "right": base,
            "left": [pygame.transform.rotate(f, 180) for f in base],
            "up": [pygame.transform.rotate(f, 90) for f in base],
            "down": [pygame.transform.rotate(f, -90) for f in base],
        }
        self.last_dir: str = "right"
        self.anim_time: float = 0.0

    def set_direction(self, name: str) -> None:
        d = DIRECTIONS.get(name)
        if d:
            self.next_direction = d

    def _try_queued_direction(self) -> None:
        if self.next_direction and self.maze.is_walkable(
            self.grid_row + self.next_direction[0],
            self.grid_col + self.next_direction[1],
        ):
            self.direction = self.next_direction
            self.next_direction = None

    def update(self, dt: float) -> None:
        if not self.direction:
            self._try_queued_direction()
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
            self._try_queued_direction()
            if self.direction and not self.maze.is_walkable(
                self.grid_row + self.direction[0],
                self.grid_col + self.direction[1],
            ):
                self.direction = None
        else:
            self.px += (dx / dist) * move
            self.py += (dy / dist) * move

        self.anim_time += dt

    def reset(self, row: int, col: int) -> None:
        self.grid_row = row
        self.grid_col = col
        self.px = col * const.TILE_SIZE
        self.py = row * const.TILE_SIZE
        self.direction = None
        self.next_direction = None

    def draw(self, screen: pygame.SurfaceType, offset_y: int = 0) -> None:
        if self.direction:
            for name, d in DIRECTIONS.items():
                if d == self.direction:
                    self.last_dir = name
                    break
        idx = int(self.anim_time * 10) % len(self.frames[self.last_dir])
        frame = self.frames[self.last_dir][idx]
        screen.blit(frame, (self.px, self.py + offset_y))
