#!/usr/bin/env python3
"""
Exercise 2: Position Tracker
Tuple manipulation
"""

from sys import argv
from math import sqrt


def dist(
    source: tuple[int, int, int],
    dest: tuple[int, int, int],
) -> float | None:
    """Calculates the distance of a pair of 3D points"""
    x1, y1, z1 = source
    x2, y2, z2 = dest
    return sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2 + (z2 - z1) ** 2)


def ft_coordinate_system(argv: list[str]) -> None:
    print("=== Game Coordinate System ===")


if __name__ == "__main__":
    ft_coordinate_system(argv)
