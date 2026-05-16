"""
The original Pacman had 28x36 cells (including the walls)
"""

from typing import TYPE_CHECKING
from pygame import SurfaceType
import pygame
from mazegenerator.mazegenerator import MazeGenerator  # type: ignore[import]
from .sprites import Spritesheet


if TYPE_CHECKING:
    from .config import Config


class Maze:
    """
    Maze render class
    """

    def __init__(self, screen: SurfaceType, conf: "Config") -> None:
        self.seed = conf.seed
        self.screen = screen
        self.TILE_SIZE = 32
        try:
            self.maze = MazeGenerator(size=(conf.width, conf.height))
            self.maze.generate(self.seed)  # Generate once at init
            self.out = self._build_maze()
            self.maze_surface = self._render_maze_to_surface()
        except Exception as e:
            print(f"Error initializing maze: {e}")
            raise

    def _build_maze(self) -> list[list[SurfaceType | None]]:
        sprite = Spritesheet("maze.png")

        N = 0b0001
        E = 0b0010
        S = 0b0100
        W = 0b1000

        # Load available sprites, use replicates for missing ones
        available_sprites = []
        for i in range(15):
            try:
                available_sprites.append(sprite.getImage(0, 32 * i))
            except Exception:
                # Use first sprite if out of range
                available_sprites.append(sprite.getImage(0, 0))

        wall_map = {i + 1: available_sprites[i] for i in range(15)}

        m_h = len(self.maze.maze)
        m_w = len(self.maze.maze[0])
        out: list[list[SurfaceType | None]] = [
            [None for _ in range(m_w * 2 + 1)] for _ in range(m_h * 2 + 1)
        ]

        checks = [
            (-1, 0, wall_map[5]),  # "│"
            (0, 1, wall_map[10]),  # "─"
            (1, 0, wall_map[5]),  # "│"
            (0, -1, wall_map[10]),  # "─"
        ]

        for i in range(len(out)):
            for j in range(len(out[i])):
                out[i][j] = None

        for mi in range(m_h):
            for mj in range(m_w):
                i = mi * 2 + 1
                j = mj * 2 + 1
                cell = self.maze.maze[mi][mj]
                if cell & N:
                    out[i - 1][j] = wall_map[10]  # "─"
                if cell & S:
                    out[i + 1][j] = wall_map[10]  # "─"
                if cell & E:
                    out[i][j + 1] = wall_map[5]  # "│"
                if cell & W:
                    out[i][j - 1] = wall_map[5]  # "│"

        for i in range(0, m_h * 2 + 1, 2):
            for j in range(0, m_w * 2 + 1, 2):
                mask = 0
                for bit, (di, dj, char) in enumerate(checks):
                    ni, nj = i + di, j + dj
                    if 0 <= ni < len(out) and 0 <= nj < len(out[ni]):
                        if out[ni][nj] == char:
                            mask |= 1 << bit
                out[i][j] = wall_map.get(mask, None)

        return out

    def _render_maze_to_surface(self) -> SurfaceType:
        """Pre-render entire maze to a single surface for faster blitting."""
        m_h = len(self.maze.maze)
        m_w = len(self.maze.maze[0])
        width = (m_w * 2 + 1) * self.TILE_SIZE
        height = (m_h * 2 + 1) * self.TILE_SIZE

        surface = pygame.Surface((width, height))
        surface.fill((0, 0, 0))

        for i, line in enumerate(self.out):
            for j, surf in enumerate(line):
                if surf is None:
                    continue
                surface.blit(surf, (j * self.TILE_SIZE, i * self.TILE_SIZE))

        return surface

    def draw(self) -> None:
        """Blit the pre-rendered maze surface."""
        self.screen.blit(self.maze_surface, (0, 0))
