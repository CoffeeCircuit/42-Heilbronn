from unittest.mock import MagicMock

from src.pac_man.ghost import Ghost


class TestGhostFreightMode:
    def setup_method(self):
        self.maze = MagicMock()
        self.ghost = Ghost(self.maze, 5, 5, (255, 0, 0))

    def test_start_freight_sets_mode(self):
        self.ghost.start_freight()
        assert self.ghost.mode == "freight"

    def test_start_freight_reduces_speed(self):
        self.ghost.start_freight()
        assert self.ghost.speed < self.ghost._base_speed

    def test_start_freight_clears_direction(self):
        self.ghost.direction = (1, 0)
        self.ghost.start_freight()
        assert self.ghost.direction is None

    def test_freight_chooses_random(self):
        self.maze.is_walkable.side_effect = lambda r, c: (
            r, c
        ) in [(4, 5), (6, 5)]
        self.ghost.start_freight()
        self.ghost.mode = "freight"
        direction = self.ghost._choose_direction()
        assert direction in [(-1, 0), (1, 0)]


class TestGhostSpawnMode:
    def setup_method(self):
        self.maze = MagicMock()
        self.ghost = Ghost(self.maze, 5, 5, (255, 0, 0))

    def test_start_spawn_sets_mode(self):
        self.ghost.start_spawn()
        assert self.ghost.mode == "spawn"

    def test_start_spawn_increases_speed(self):
        self.ghost.start_spawn()
        assert self.ghost.speed > self.ghost._base_speed

    def test_start_spawn_goal_is_home(self):
        self.ghost._home = (1, 1)
        self.ghost.start_spawn()
        assert self.ghost.goal == (1, 1)

    def test_spawn_uses_bfs_path(self):
        walkable = {(4, 5), (3, 5), (2, 5), (1, 5), (0, 5),
                    (6, 5)}
        self.maze.is_walkable.side_effect = lambda r, c: (
            r, c
        ) in walkable
        self.maze.out = [[None] * 6 for _ in range(7)]
        self.ghost._home = (0, 5)
        self.ghost.start_spawn()
        direction = self.ghost._choose_direction()
        assert direction == (-1, 0)


class TestGhostIdleMode:
    def setup_method(self):
        self.maze = MagicMock()
        self.ghost = Ghost(self.maze, 5, 5, (255, 0, 0))

    def test_go_idle_sets_mode(self):
        self.ghost.go_idle()
        assert self.ghost.mode == "idle"

    def test_go_idle_zero_speed(self):
        self.ghost.go_idle()
        assert self.ghost.speed == 0.0

    def test_idle_returns_no_direction(self):
        self.ghost.go_idle()
        self.maze.is_walkable.side_effect = lambda r, c: True
        assert self.ghost._choose_direction() is None

    def test_idle_update_does_nothing(self):
        self.ghost.go_idle()
        self.ghost.direction = (1, 0)
        self.ghost.update(0.1)
        assert self.ghost.px == 5 * 32
        assert self.ghost.py == 5 * 32


class TestGhostGoNormal:
    def setup_method(self):
        self.maze = MagicMock()
        self.ghost = Ghost(self.maze, 5, 5, (255, 0, 0))

    def test_go_normal_sets_mode(self):
        self.ghost.start_freight()
        self.ghost.go_normal("chase")
        assert self.ghost.mode == "chase"

    def test_go_normal_restores_speed(self):
        self.ghost.start_freight()
        self.ghost.go_normal("scatter")
        assert self.ghost.speed == self.ghost._base_speed
