#!/usr/bin/env python3
"""
Exercise 2: Position Tracker
$ python ./ex2/ft_coordinate_system.py "$(python data_generator.py 2)
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
    print()
    arg_list = argv[1][2:-2]
    for coord in arg_list.split("), ("):
        x, y, z = coord.split(", ")
        try:
            print(f"Parsing coordinates: '{x}, {y}, {z}'")
            x, y, z = int(x), int(y), int(z)
            print(f"Parsed position: ({x}, {y}, {z})")
            d = dist((0, 0, 0), (x, y, z))
            print(f"Distance between (0, 0, 0) and ({x}, {y}, {z}): {d:.2f}")
            print()
        except ValueError as e:
            print("Error: ", e)
            print()


if __name__ == "__main__":
    ft_coordinate_system(argv)
