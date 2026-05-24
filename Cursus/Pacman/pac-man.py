#!/usr/bin/env python3
import sys
from src.pac_man import pacman

if __name__ == "__main__":
    config_file = sys.argv[1] if len(sys.argv) > 1 else "config.json"
    pacman(config_file)
