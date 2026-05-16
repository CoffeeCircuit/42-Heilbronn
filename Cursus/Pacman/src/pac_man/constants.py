from typing import Sequence

# Sprite and display constants
TILE_SIZE = 32  # pixels
PACMAN_SPEED = 2  # tiles per frame
GHOST_SPEED = 1.5

# Colors (RGB tuples)
COLOR_BLACK = (0, 0, 0)
COLOR_WHITE = (255, 255, 255)
COLOR_YELLOW = (255, 255, 0)
COLOR_RED = (255, 0, 0)

# Game states
STATE_PLAYING = "playing"
STATE_GAME_OVER = "game_over"
STATE_PAUSE = "pause"

__all__: Sequence[str] = [
    "TILE_SIZE",
    "PACMAN_SPEED",
    "GHOST_SPEED",
    "COLOR_BLACK",
    "COLOR_WHITE",
    "COLOR_YELLOW",
    "COLOR_RED",
    "STATE_PLAYING",
    "STATE_GAME_OVER",
    "STATE_PAUSE",
]
