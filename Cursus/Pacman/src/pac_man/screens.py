from abc import ABC, abstractmethod
import re

import pygame

from . import constants as const
from .font import Text
from .game import Game
from .highscore import Highscore


class Screen(ABC):
    @abstractmethod
    def handle_event(
        self, event: pygame.event.Event
    ) -> str | None:
        """Return new state name or None."""

    @abstractmethod
    def update(self, dt: float) -> str | None:
        """Return new state name or None."""

    @abstractmethod
    def draw(self) -> None:
        """Draw to screen."""


class TitleScreen(Screen):
    def __init__(
        self,
        screen: pygame.SurfaceType,
        font: Text,
        small_font: Text,
        highscore: Highscore,
    ) -> None:
        self.screen = screen
        self.font = font
        self.small_font = small_font
        self.highscore = highscore
        self._selected: int = 0
        self._options = [
            "START GAME",
            "HIGHSCORES",
            "INSTRUCTIONS",
            "EXIT",
        ]
        self._blink_timer: float = 0.0
        self._blink_visible: bool = True

    def handle_event(
        self, event: pygame.event.Event
    ) -> str | None:
        if event.type != pygame.KEYDOWN:
            return None
        if event.key in (pygame.K_UP, pygame.K_w):
            self._selected = (self._selected - 1) % len(
                self._options
            )
        elif event.key in (pygame.K_DOWN, pygame.K_s):
            self._selected = (self._selected + 1) % len(
                self._options
            )
        elif event.key == pygame.K_RETURN:
            if self._selected == 0:
                return const.STATE_WAITING
            elif self._selected == 1:
                return const.STATE_HIGHSCORES
            elif self._selected == 2:
                return const.STATE_INSTRUCTIONS
            elif self._selected == 3:
                pygame.quit()
                exit()
        return None

    def update(self, dt: float) -> str | None:
        self._blink_timer += dt
        if self._blink_timer >= 0.5:
            self._blink_timer = 0.0
            self._blink_visible = not self._blink_visible
        return None

    def draw(self) -> None:
        w = self.screen.get_width()
        h = self.screen.get_height()
        title = self.font.render("PAC-MAN")
        self.screen.blit(
            title, ((w - title.get_width()) // 2, h // 6)
        )
        for i, opt in enumerate(self._options):
            color = (
                const.COLOR_YELLOW
                if i == self._selected
                else const.COLOR_WHITE
            )
            self.font.color = color
            surf = self.font.render(opt)
            self.screen.blit(
                surf, ((w - surf.get_width()) // 2, h // 2 + i * 40)
            )
        self.font.color = const.COLOR_WHITE
        if self.highscore.entries:
            hs = self.small_font.render("TOP SCORES")
            self.screen.blit(
                hs, ((w - hs.get_width()) // 2, h * 3 // 4)
            )
            for i, entry in enumerate(
                self.highscore.entries[:3]
            ):
                name = entry["name"]
                score = entry["score"]
                line = self.small_font.render(
                    f"{i + 1}. {name} {score}"
                )
                self.screen.blit(
                    line,
                    ((w - line.get_width()) // 2,
                     h * 3 // 4 + 25 + i * 22),
                )


class WaitingScreen(Screen):
    def __init__(
        self,
        screen: pygame.SurfaceType,
        font: Text,
        game: Game,
    ) -> None:
        self.screen = screen
        self.font = font
        self.game = game
        self._blink_timer: float = 0.0
        self._blink_visible: bool = True

    def handle_event(
        self, event: pygame.event.Event
    ) -> str | None:
        if (event.type == pygame.KEYDOWN
                and event.key == pygame.K_SPACE):
            return const.STATE_PLAYING
        return None

    def update(self, dt: float) -> str | None:
        self._blink_timer += dt
        if self._blink_timer >= 0.5:
            self._blink_timer = 0.0
            self._blink_visible = not self._blink_visible
        return None

    def draw(self) -> None:
        self.game.draw()
        if self._blink_visible:
            w = self.screen.get_width()
            h = self.screen.get_height()
            surf = self.font.render("PRESS SPACE")
            self.screen.blit(
                surf, ((w - surf.get_width()) // 2, h // 2)
            )


class PauseScreen(Screen):
    def __init__(
        self,
        screen: pygame.SurfaceType,
        font: Text,
        game: Game,
    ) -> None:
        self.screen = screen
        self.font = font
        self.game = game

    def handle_event(
        self, event: pygame.event.Event
    ) -> str | None:
        if event.type != pygame.KEYDOWN:
            return None
        if event.key == pygame.K_SPACE:
            self.game.state = const.STATE_PLAYING
            return const.STATE_PLAYING
        elif event.key == pygame.K_ESCAPE:
            return const.STATE_TITLE
        return None

    def update(self, dt: float) -> str | None:
        return None

    def draw(self) -> None:
        self.game.draw()
        w = self.screen.get_width()
        h = self.screen.get_height()
        overlay = pygame.Surface((w, h))
        overlay.set_alpha(128)
        overlay.fill((0, 0, 0))
        self.screen.blit(overlay, (0, 0))
        pause = self.font.render("PAUSED")
        self.screen.blit(
            pause, ((w - pause.get_width()) // 2, h // 3)
        )
        resume = self.font.render("SPACE - RESUME")
        self.screen.blit(
            resume, ((w - resume.get_width()) // 2, h // 2)
        )
        menu = self.font.render("ESC - MENU")
        self.screen.blit(
            menu, ((w - menu.get_width()) // 2, h // 2 + 30)
        )


class GameOverScreen(Screen):
    def __init__(
        self,
        screen: pygame.SurfaceType,
        font: Text,
        game: Game,
    ) -> None:
        self.screen = screen
        self.font = font
        self.game = game

    def handle_event(
        self, event: pygame.event.Event
    ) -> str | None:
        if (event.type == pygame.KEYDOWN
                and event.key == pygame.K_RETURN):
            return const.STATE_NAME_ENTRY
        return None

    def update(self, dt: float) -> str | None:
        return None

    def draw(self) -> None:
        self.game.draw()
        w = self.screen.get_width()
        h = self.screen.get_height()
        go = self.font.render("GAME OVER")
        self.screen.blit(
            go, ((w - go.get_width()) // 2, h // 3)
        )
        score = self.font.render(
            f"SCORE: {self.game.score}"
        )
        self.screen.blit(
            score,
            ((w - score.get_width()) // 2, h // 3 + 40),
        )
        prompt = self.font.render("PRESS ENTER")
        self.screen.blit(
            prompt,
            ((w - prompt.get_width()) // 2, h // 3 + 80),
        )


class VictoryScreen(Screen):
    def __init__(
        self,
        screen: pygame.SurfaceType,
        font: Text,
        game: Game,
    ) -> None:
        self.screen = screen
        self.font = font
        self.game = game

    def handle_event(
        self, event: pygame.event.Event
    ) -> str | None:
        if (event.type == pygame.KEYDOWN
                and event.key == pygame.K_RETURN):
            return const.STATE_NAME_ENTRY
        return None

    def update(self, dt: float) -> str | None:
        return None

    def draw(self) -> None:
        self.game.draw()
        w = self.screen.get_width()
        h = self.screen.get_height()
        win = self.font.render("YOU WIN!")
        self.screen.blit(
            win, ((w - win.get_width()) // 2, h // 3)
        )
        score = self.font.render(
            f"SCORE: {self.game.score}"
        )
        self.screen.blit(
            score,
            ((w - score.get_width()) // 2, h // 3 + 40),
        )
        prompt = self.font.render("PRESS ENTER")
        self.screen.blit(
            prompt,
            ((w - prompt.get_width()) // 2, h // 3 + 80),
        )


class NameEntryScreen(Screen):
    def __init__(
        self,
        screen: pygame.SurfaceType,
        font: Text,
        small_font: Text,
        highscore: Highscore,
        score: int,
    ) -> None:
        self.screen = screen
        self.font = font
        self.small_font = small_font
        self.highscore = highscore
        self.score = score
        self._name: str = ""
        self._cursor_timer: float = 0.0
        self._cursor_visible: bool = True

    def handle_event(
        self, event: pygame.event.Event
    ) -> str | None:
        if event.type != pygame.KEYDOWN:
            return None
        if event.key == pygame.K_RETURN:
            name = self._name.strip() or "ANON"
            self.highscore.add(name, self.score)
            self.highscore.save()
            return const.STATE_TITLE
        elif event.key == pygame.K_BACKSPACE:
            self._name = self._name[:-1]
        elif event.key == pygame.K_ESCAPE:
            return const.STATE_TITLE
        else:
            ch = event.unicode
            if ch and len(self._name) < 10:
                if re.match(r"[a-zA-Z0-9 ]", ch):
                    self._name += ch
        return None

    def update(self, dt: float) -> str | None:
        self._cursor_timer += dt
        if self._cursor_timer >= 0.5:
            self._cursor_timer = 0.0
            self._cursor_visible = not self._cursor_visible
        return None

    def draw(self) -> None:
        w = self.screen.get_width()
        h = self.screen.get_height()
        prompt = self.font.render("ENTER YOUR NAME")
        self.screen.blit(
            prompt,
            ((w - prompt.get_width()) // 2, h // 6),
        )
        cursor = "_" if self._cursor_visible else " "
        name_surf = self.font.render(f"{self._name}{cursor}")
        self.screen.blit(
            name_surf,
            ((w - name_surf.get_width()) // 2, h // 3),
        )
        score_surf = self.font.render(
            f"SCORE: {self.score}"
        )
        self.screen.blit(
            score_surf,
            ((w - score_surf.get_width()) // 2, h // 3 + 40),
        )
        hs_title = self.small_font.render("TOP SCORES")
        self.screen.blit(
            hs_title,
            ((w - hs_title.get_width()) // 2, h // 2),
        )
        for i, entry in enumerate(
            self.highscore.entries[:10]
        ):
            line = self.small_font.render(
                f"{i + 1}. {entry['name']:>10}"
                f" {entry['score']}"
            )
            self.screen.blit(
                line,
                ((w - line.get_width()) // 2,
                 h // 2 + 25 + i * 20),
            )


class HighscoresScreen(Screen):
    def __init__(
        self,
        screen: pygame.SurfaceType,
        font: Text,
        highscore: Highscore,
    ) -> None:
        self.screen = screen
        self.font = font
        self.highscore = highscore

    def handle_event(
        self, event: pygame.event.Event
    ) -> str | None:
        if (event.type == pygame.KEYDOWN
                and event.key in (
                    pygame.K_ESCAPE, pygame.K_RETURN)):
            return const.STATE_TITLE
        return None

    def update(self, dt: float) -> str | None:
        return None

    def draw(self) -> None:
        w = self.screen.get_width()
        h = self.screen.get_height()
        title = self.font.render("HIGHSCORES")
        self.screen.blit(
            title, ((w - title.get_width()) // 2, 20),
        )
        for i, entry in enumerate(
            self.highscore.entries[:10]
        ):
            line = self.font.render(
                f"{i + 1}. {entry['name']:>10}"
                f" {entry['score']}"
            )
            self.screen.blit(
                line,
                ((w - line.get_width()) // 2, 60 + i * 30),
            )
        back = self.font.render("ESC - BACK")
        self.screen.blit(
            back,
            ((w - back.get_width()) // 2, h - 40),
        )


class InstructionsScreen(Screen):
    def __init__(
        self,
        screen: pygame.SurfaceType,
        font: Text,
    ) -> None:
        self.screen = screen
        self.font = font
        self._lines = [
            "CONTROLS:",
            "",
            "ARROWS / WASD - MOVE",
            "SPACE - PAUSE",
            "ENTER - SELECT",
            "ESC - BACK",
            "",
            "RULES:",
            "",
            "EAT ALL PACGUMS TO WIN",
            "SUPER PACGUMS LET YOU",
            "  EAT GHOSTS",
            "AVOID GHOSTS OR DIE",
            "COMPLETE 10 LEVELS",
            "  TO WIN THE GAME",
        ]

    def handle_event(
        self, event: pygame.event.Event
    ) -> str | None:
        if (event.type == pygame.KEYDOWN
                and event.key in (
                    pygame.K_ESCAPE, pygame.K_RETURN)):
            return const.STATE_TITLE
        return None

    def update(self, dt: float) -> str | None:
        return None

    def draw(self) -> None:
        w = self.screen.get_width()
        for i, line in enumerate(self._lines):
            surf = self.font.render(line)
            self.screen.blit(
                surf,
                ((w - surf.get_width()) // 2, 20 + i * 28),
            )
