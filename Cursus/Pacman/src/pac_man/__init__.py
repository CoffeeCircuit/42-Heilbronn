import sys
from .pacman import pacman


def main() -> None:
    if len(sys.argv) != 2:
        print("Error: config file required")
        sys.exit(1)
    pacman(sys.argv[1])
