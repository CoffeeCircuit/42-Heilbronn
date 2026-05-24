import time

import pygame

from . import constants as const
from .config import Config
from .font import Text
from .game import Game
from .highscore import Highscore
from .screens import (
    GameOverScreen,
    HighscoresScreen,
    InstructionsScreen,
    NameEntryScreen,
    PauseScreen,
    Screen,
    TitleScreen,
    VictoryScreen,
    WaitingScreen,
)

STATE_LEVEL_COMPLETE = "level_complete"


class App:
    def __init__(
        self, cfg: Config, screen: pygame.SurfaceType
    ) -> None:
        self.cfg = cfg
        self.screen = screen
        self.font = Text()
        self.small_font = Text()
        self.small_font.size = 16
        self.small_font.font = pygame.font.Font(
            self.small_font.path, 16
        )
        self.highscore = Highscore(cfg.highscore_filename)
        self.highscore.load()
        self.game: Game = None  # type: ignore[assignment]
        self._screen: Screen = None  # type: ignore[assignment]
        self._state: str = const.STATE_TITLE
        self._transition(const.STATE_TITLE)

    def _transition(self, new_state: str) -> None:
        if new_state == const.STATE_TITLE:
            self._screen = TitleScreen(
                self.screen, self.font,
                self.small_font, self.highscore,
            )
        elif new_state == const.STATE_WAITING:
            if self.game is None:
                self.game = Game(self.cfg, self.screen)
            self._screen = WaitingScreen(
                self.screen, self.font, self.game,
            )
        elif new_state == const.STATE_PLAYING:
            self.game.state = const.STATE_PLAYING
            self._screen = _GameScreen(self.game)
        elif new_state == const.STATE_PAUSE:
            self._screen = PauseScreen(
                self.screen, self.small_font, self.game,
            )
        elif new_state == const.STATE_GAME_OVER:
            self._screen = GameOverScreen(
                self.screen, self.font, self.game,
            )
        elif new_state == const.STATE_VICTORY:
            self._screen = VictoryScreen(
                self.screen, self.font, self.game,
            )
        elif new_state == const.STATE_NAME_ENTRY:
            self._screen = NameEntryScreen(
                self.screen, self.font,
                self.small_font, self.highscore,
                self.game.score,
            )
        elif new_state == const.STATE_HIGHSCORES:
            self._screen = HighscoresScreen(
                self.screen, self.small_font, self.highscore,
            )
        elif new_state == const.STATE_INSTRUCTIONS:
            self._screen = InstructionsScreen(
                self.screen, self.small_font,
            )
        self._state = new_state

    def handle_event(
        self, event: pygame.event.Event
    ) -> None:
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
        if self._state == const.STATE_PLAYING:
            self.game.handle_event(event)
            self._check_game_state()
        elif self._state == STATE_LEVEL_COMPLETE:
            pass
        else:
            result = self._screen.handle_event(event)
            if result == const.STATE_WAITING:
                self.game = Game(self.cfg, self.screen)
                self._transition(const.STATE_WAITING)
            elif result is not None:
                self._transition(result)

    def update(self, dt: float) -> None:
        if self._state == const.STATE_PLAYING:
            self.game.update(dt)
            self._check_game_state()
        elif self._state == STATE_LEVEL_COMPLETE:
            self.game.update(dt)
            self._check_game_state()
        else:
            result = self._screen.update(dt)
            if result is not None:
                self._transition(result)

    def _check_game_state(self) -> None:
        s = self.game.state
        if s == const.STATE_PAUSE:
            self._transition(const.STATE_PAUSE)
        elif s == const.STATE_GAME_OVER:
            self._transition(const.STATE_GAME_OVER)
        elif s == const.STATE_VICTORY:
            self._transition(const.STATE_VICTORY)
        elif s == STATE_LEVEL_COMPLETE:
            if self._state != STATE_LEVEL_COMPLETE:
                self._state = STATE_LEVEL_COMPLETE

    def draw(self) -> None:
        self._screen.draw()


class _GameScreen(Screen):
    def __init__(self, game: Game) -> None:
        self.game = game

    def handle_event(
        self, event: pygame.event.Event
    ) -> str | None:
        return None

    def update(self, dt: float) -> str | None:
        return None

    def draw(self) -> None:
        self.game.draw()

# TODO this might have to be ASYNC because of pygbag
def pacman(cfg_file_path: str) -> None:
    cfg = Config()
    if not cfg.read(cfg_file_path):
        exit()
    pygame.init()
    w = (cfg.width * 2 + 1) * const.TILE_SIZE
    h = (
        (cfg.height * 2 + 1) * const.TILE_SIZE
        + const.HUD_HEIGHT
    )
    screen = pygame.display.set_mode((w, h), vsync=1)
    pygame.display.set_caption("Pac-Man")
    app = App(cfg, screen)
    fps = 60
    cap = 1.0 / fps
    last = time.perf_counter()
    while True:
        for event in pygame.event.get():
            app.handle_event(event)
        now = time.perf_counter()
        dt = min(now - last, cap)
        last = now
        app.update(dt)
        screen.fill((0, 0, 0))
        app.draw()
        pygame.display.flip()
