from unittest.mock import MagicMock, patch

from src.pac_man.ghost import Ghost
from src.pac_man.player import Player


class TestPlayerReset:
    def setup_method(self):
        self.maze = MagicMock()
        self.maze.center = (5, 5)
        with patch("src.pac_man.player.Spritesheet"), \
             patch("pygame.transform.rotate"):
            self.player = Player(self.maze)

    def test_reset_position(self):
        self.player.reset(10, 20)
        assert self.player.grid_row == 10
        assert self.player.grid_col == 20
        assert self.player.px == 20 * 32
        assert self.player.py == 10 * 32

    def test_reset_clears_direction(self):
        self.player.direction = (1, 0)
        self.player.next_direction = (0, 1)
        self.player.reset(5, 5)
        assert self.player.direction is None
        assert self.player.next_direction is None


class TestGhostReset:
    def setup_method(self):
        self.maze = MagicMock()
        self.ghost = Ghost(self.maze, 5, 5, (255, 0, 0))

    def test_reset_position(self):
        self.ghost.reset(10, 20)
        assert self.ghost.grid_row == 10
        assert self.ghost.grid_col == 20
        assert self.ghost.px == 20 * 32
        assert self.ghost.py == 10 * 32

    def test_reset_clears_direction(self):
        self.ghost.direction = (1, 0)
        self.ghost.reset(5, 5)
        assert self.ghost.direction is None

    def test_reset_sets_scatter_mode(self):
        self.ghost.mode = "chase"
        self.ghost.reset(5, 5)
        assert self.ghost.mode == "scatter"
