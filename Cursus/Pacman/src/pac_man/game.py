import pygame

from . import constants as const
from .config import Config
from .font import Text
from .ghost import Ghost
from .maze import Maze
from .pacgums import Pacgums
from .player import Player

GHOST_DEFS = [
    (const.COLOR_RED, "tl", "tr"),
    (const.COLOR_PINK, "tr", "tl"),
    (const.COLOR_TEAL, "bl", "br"),
    (const.COLOR_ORANGE, "br", "bl"),
]

STATE_LEVEL_COMPLETE = "level_complete"


class Game:
    def __init__(self, cfg: Config, screen: pygame.SurfaceType) -> None:
        self.cfg = cfg
        self.screen = screen
        self.score: int = 0
        self.lives: int = cfg.lives
        self.level_number: int = 1
        self.hud_offset = const.HUD_HEIGHT
        self.state: str = const.STATE_PLAYING
        self._invincible_timer: float = 0.0
        self._pause_timer: float = 0.0
        self._freight_timer: float = 0.0
        self._ghost_points: int = 200
        self._mode_timer: float = 0.0
        self._current_mode: str = "scatter"
        self._current_freight_time: float = const.FREIGHT_TIME
        self._level_timer: float = float(cfg.level_max_time)

        self._font = Text()
        self._small_font = Text()
        self._small_font.size = 16
        self._small_font.font = pygame.font.Font(
            self._small_font.path, 16
        )
        self.maze: Maze = None  # type: ignore[assignment]
        self.player: Player = None  # type: ignore[assignment]
        self.pacgums: Pacgums = None  # type: ignore[assignment]
        self.ghosts: list[Ghost] = []
        self._player_spawn: tuple[int, int] = (1, 1)
        self._ghost_spawns: list[tuple[int, int]] = []
        self._life_icon: pygame.Surface = None  # type: ignore[assignment]

        self._init_level(cfg.seed)

    def _init_level(self, seed: int) -> None:
        self.maze = Maze(self.screen, self.cfg, seed=seed)
        if not hasattr(self, 'player') or self.player is None:
            self.player = Player(self.maze)
            self._life_icon = pygame.transform.scale(
                self.player.frames["right"][1], (24, 24)
            )
        else:
            self.player.maze = self.maze

        spawn = self.maze.center
        self._player_spawn = spawn
        self.pacgums = Pacgums(self.maze, {spawn})

        rows = len(self.maze.out)
        cols = len(self.maze.out[0])
        corners: dict[str, tuple[int, int]] = {
            "tl": (0, 0),
            "tr": (0, cols - 1),
            "bl": (rows - 1, 0),
            "br": (rows - 1, cols - 1),
        }

        self._ghost_spawns = self._find_ghost_spawns()
        if not self.ghosts:
            for i, (color, _, scatter_key) in enumerate(GHOST_DEFS):
                r, c = self._ghost_spawns[i]
                self.ghosts.append(
                    Ghost(self.maze, r, c, color, corners[scatter_key])
                )
        else:
            for i, g in enumerate(self.ghosts):
                r, c = self._ghost_spawns[i]
                g.maze = self.maze
                g.reset(r, c)
                g.scatter_goal = corners[GHOST_DEFS[i][2]]

        ghost_speed = (
            (const.GHOST_SPEED + self.level_number
             * const.GHOST_SPEED_PER_LEVEL) * const.TILE_SIZE
        )
        for g in self.ghosts:
            g.set_base_speed(ghost_speed)

        self._current_freight_time = max(
            const.FREIGHT_TIME
            - (self.level_number - 1) * const.FREIGHT_TIME_DECREASE,
            const.MIN_FREIGHT_TIME,
        )

        self.player.reset(*self._player_spawn)
        self._mode_timer = 0.0
        self._current_mode = "scatter"
        self._freight_timer = 0.0
        self._level_timer = float(self.cfg.level_max_time)

    def handle_event(self, event: pygame.event.Event) -> None:
        if event.type != pygame.KEYDOWN:
            return
        if event.key == pygame.K_SPACE:
            if self.state == const.STATE_PLAYING:
                self.state = const.STATE_PAUSE
                return
            elif self.state == const.STATE_PAUSE:
                self.state = const.STATE_PLAYING
                return
        key_map = {
            pygame.K_UP: "up", pygame.K_w: "up",
            pygame.K_DOWN: "down", pygame.K_s: "down",
            pygame.K_LEFT: "left", pygame.K_a: "left",
            pygame.K_RIGHT: "right", pygame.K_d: "right",
        }
        direction = key_map.get(event.key)
        if direction:
            self.player.set_direction(direction)

    def update(self, dt: float) -> None:
        if self.state == const.STATE_GAME_OVER:
            return
        if self.state == STATE_LEVEL_COMPLETE:
            self._pause_timer -= dt
            if self._pause_timer <= 0:
                self._advance_level()
            return
        if self.state != const.STATE_PLAYING:
            return
        if self._pause_timer > 0:
            self._pause_timer = max(0.0, self._pause_timer - dt)
            return
        self._invincible_timer = max(0.0, self._invincible_timer - dt)
        self._level_timer -= dt
        if self._level_timer <= 0:
            self._level_timer = 0
            self.state = const.STATE_GAME_OVER
            return
        if self._freight_timer > 0:
            self._freight_timer = max(0.0, self._freight_timer - dt)
            if self._freight_timer <= 0:
                self._end_freight()
        self.player.update(dt)
        self.pacgums.update(dt)
        self._check_eating()
        self._update_mode(dt)
        self._update_ghost_goals()
        for g in self.ghosts:
            g.update(dt)
            if g.mode == "spawn" and g.direction is None:
                g.go_idle()
        self._check_ghost_collision()

    def _check_eating(self) -> None:
        kind = self.pacgums.eat(
            self.player.grid_row, self.player.grid_col
        )
        if kind == "pacgum":
            self.score += self.cfg.points_per_pacgum
        elif kind == "super":
            self.score += self.cfg.points_per_super_pacgum
            self._start_freight()
        if self.pacgums.remaining == 0:
            if self.level_number >= const.NUM_LEVELS:
                self.state = const.STATE_VICTORY
            else:
                self.state = STATE_LEVEL_COMPLETE
                self._pause_timer = const.LEVEL_COMPLETE_PAUSE

    def _start_freight(self) -> None:
        self._freight_timer = self._current_freight_time
        self._ghost_points = 200
        for g in self.ghosts:
            g.start_freight()

    def _end_freight(self) -> None:
        for g in self.ghosts:
            if g.mode not in ("scatter", "chase"):
                g.go_normal(self._current_mode)

    def _update_mode(self, dt: float) -> None:
        self._mode_timer += dt
        if (self._current_mode == "scatter"
                and self._mode_timer >= const.SCATTER_TIME):
            self._current_mode = "chase"
            self._mode_timer = 0.0
        elif (self._current_mode == "chase"
                and self._mode_timer >= const.CHASE_TIME):
            self._current_mode = "scatter"
            self._mode_timer = 0.0

    def _update_ghost_goals(self) -> None:
        pr = self.player.grid_row
        pc = self.player.grid_col
        for g in self.ghosts:
            if g.mode in ("freight", "spawn", "idle"):
                continue
            if self._current_mode == "scatter":
                g.set_goal(*g.scatter_goal)
            else:
                g.set_goal(pr, pc)

    def _check_ghost_collision(self) -> None:
        if self._invincible_timer > 0:
            return
        for g in self.ghosts:
            if not (g.grid_row == self.player.grid_row
                    and g.grid_col == self.player.grid_col):
                continue
            if g.mode == "freight":
                self.score += self._ghost_points
                self._ghost_points *= 2
                g.start_spawn()
            elif g.mode in ("scatter", "chase"):
                self.lives -= 1
                if self.lives <= 0:
                    self.state = const.STATE_GAME_OVER
                else:
                    self._reset_positions()
                    self._pause_timer = 1.0
                    self._invincible_timer = const.INVINCIBLE_TIME
                return

    def _reset_positions(self) -> None:
        self.player.reset(*self._player_spawn)
        for i, g in enumerate(self.ghosts):
            g.reset(*self._ghost_spawns[i])
        self._mode_timer = 0.0
        self._current_mode = "scatter"
        self._freight_timer = 0.0

    def _advance_level(self) -> None:
        if self.level_number >= const.NUM_LEVELS:
            self.state = const.STATE_VICTORY
            return
        self.level_number += 1
        new_seed = self.cfg.seed + self.level_number - 1
        self._init_level(new_seed)
        self.state = const.STATE_PLAYING

    def _restart_game(self) -> None:
        self.score = 0
        self.lives = self.cfg.lives
        self.level_number = 1
        self.state = const.STATE_PLAYING
        self._invincible_timer = 0.0
        self._freight_timer = 0.0
        self._ghost_points = 200
        self._init_level(self.cfg.seed)

    def _find_ghost_spawns(self) -> list[tuple[int, int]]:
        rows = len(self.maze.out)
        cols = len(self.maze.out[0])
        corners = [
            (1, 1),
            (1, cols - 2),
            (rows - 2, 1),
            (rows - 2, cols - 2),
        ]
        return [
            self.maze.nearest_cell(r, c) for r, c in corners
        ]

    def draw(self) -> None:
        self.maze.draw(self.hud_offset)
        self.pacgums.draw(self.screen, self.hud_offset)
        self.player.draw(self.screen, self.hud_offset)
        for g in self.ghosts:
            g.draw(self.screen, self.hud_offset)
        self._draw_hud()

    def _draw_hud(self) -> None:
        screen_w = self.screen.get_width()

        score_surf = self._font.render(f"{self.score}")
        self.screen.blit(score_surf, (8, 4))

        level_surf = self._small_font.render(
            f"Lv.{self.level_number}"
        )
        level_x = screen_w // 2 - level_surf.get_width() - 10
        self.screen.blit(level_surf, (level_x, 12))

        secs = int(self._level_timer)
        time_surf = self._small_font.render(
            f"{secs // 60}:{secs % 60:02d}"
        )
        time_x = screen_w // 2 + 10
        self.screen.blit(time_surf, (time_x, 12))

        icon_w = self._life_icon.get_width()
        start_x = screen_w - (self.lives * (icon_w + 4)) - 4
        for i in range(self.lives):
            self.screen.blit(
                self._life_icon, (start_x + i * (icon_w + 4), 8)
            )
