from unittest.mock import MagicMock
from src.pac_man.ghost import Ghost, REVERSE


class TestGhostDirection:
    def setup_method(self):
        self.maze = MagicMock()
        self.ghost = Ghost(self.maze, 5, 5, (255, 0, 0))

    def test_choose_single_direction(self):
        self.maze.is_walkable.side_effect = lambda r, c: (r, c) == (4, 5)
        result = self.ghost._choose_direction()
        assert result == (-1, 0)

    def test_choose_closest_to_goal(self):
        self.maze.is_walkable.side_effect = lambda r, c: (r, c) in [
            (4, 5), (6, 5), (5, 4), (5, 6)
        ]
        self.ghost.set_goal(0, 0)
        result = self.ghost._choose_direction()
        assert result == (-1, 0)

    def test_no_uturn(self):
        self.ghost.direction = (-1, 0)
        self.maze.is_walkable.side_effect = lambda r, c: (r, c) in [
            (4, 5), (6, 5), (5, 4), (5, 6)
        ]
        options = self.ghost._get_walkable_directions()
        assert (1, 0) not in options

    def test_uturn_allowed_if_only_option(self):
        self.ghost.direction = (-1, 0)
        self.maze.is_walkable.side_effect = lambda r, c: (r, c) == (6, 5)
        options = self.ghost._get_walkable_directions(exclude_reverse=False)
        assert (1, 0) in options

    def test_reverse_map(self):
        assert REVERSE[(-1, 0)] == (1, 0)
        assert REVERSE[(1, 0)] == (-1, 0)
        assert REVERSE[(0, -1)] == (0, 1)
        assert REVERSE[(0, 1)] == (0, -1)

    def test_set_goal(self):
        self.ghost.set_goal(10, 20)
        assert self.ghost.goal == (10, 20)

    def test_initial_mode(self):
        assert self.ghost.mode == "scatter"

    def test_initial_position(self):
        assert self.ghost.grid_row == 5
        assert self.ghost.grid_col == 5
