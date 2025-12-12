#!/usr/bin/env python3


class Plant:
    """Plant class"""
    count = 0

    def __init__(self, name: str, height: int, age: int):
        self._name = name
        self._height = height
        self._age = age
        print(f"Created: {self._name} ({self._height}cm, {self._age} days)")
        Plant.count += 1


def main():
    print("=== Plant Factory Output ===")
    Plant("Rose", 25, 30)
    Plant("Oak", 200, 365)
    Plant("Cactus", 5, 90)
    Plant("Sunflower", 80, 45)
    Plant("Fern", 15, 120)
    print()
    print(f"Total plants created: {Plant.count}")


if __name__ == "__main__":
    main()
