#!/usr/bin/env python3


class Plant:
    """Plant class"""

    def __init__(self, name: str, height: int, age: int):
        self.created = 1
        self._name = name
        self._height = height
        self._age = age
        print(f"Created: {self._name} ({self._height}cm, {self._age} days)")


def main():
    print("=== Plant Factory Output ===")
    total = 0
    total += Plant("Rose", 25, 30).created
    total += Plant("Oak", 200, 365).created
    total += Plant("Cactus", 5, 90).created
    total += Plant("Sunflower", 80, 45).created
    total += Plant("Fern", 15, 120).created
    print()
    print(f"Total plants created: {total}")


if __name__ == "__main__":
    main()
