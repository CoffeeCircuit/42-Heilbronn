#!/usr/bin/env python3
"""
Directory: ex2/
Files to Submit: ft_coordinate_system.py
Authorized: import sys, sys.argv, import math, tuple(), int(), float(),
print(), split(), try/except, math.sqrt()
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
    """
    Calculates the distance between 0,0,0 and the tuple from argv

    :param argv: Command line arguments
    :type argv: list[str]
    """
    print("=== Game Coordinate System ===")
    print()
    args = argv[1:] if len(argv) > 1 else ["10,20,5", "3,4,0", "abc,def,ghi"]
    for coord in args:
        try:
            x, y, z = coord.split(",")
            print(f'Parsing coordinates: "{x},{y},{z}"')
            x, y, z = int(x), int(y), int(z)
            print(f"Parsed position: ({x}, {y}, {z})")
            d = dist((0, 0, 0), (x, y, z))
            print(f"Distance between (0, 0, 0) and ({x}, {y}, {z}): {d:.2f}")
            print()
        except ValueError as e:
            print("Error parsing coordinates: ", e)
            print(f"Error details - Type: {type(e).__name__}, Args: {e.args}")
            print()
    x, y, z = (int(v) for v in args[0].split(","))
    print("Unpacking demonstration:")
    print("Player at: ", f"{x=}, {y=}, {z=}")
    print("Coordinates: ", f"X={x}, Y={y}, Z={z}")


if __name__ == "__main__":
    ft_coordinate_system(argv)
