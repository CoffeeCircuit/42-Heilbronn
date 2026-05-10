#!/usr/bin/env python3
import sys
from src.pac_man import pacman

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Error: config file required")
        sys.exit(1)
    else:
        pacman(sys.argv[1])
