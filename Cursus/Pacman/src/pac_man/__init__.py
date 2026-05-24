import sys
from .pacman import pacman


def main() -> None:
    if len(sys.argv) != 2:
        pacman("config.json")
    pacman(sys.argv[1])
