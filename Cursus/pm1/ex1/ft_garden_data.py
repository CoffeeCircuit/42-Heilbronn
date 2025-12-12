#!/usr/bin/env python3


class Plant:
    """Plant class"""

    def __init__(self, name: str, height: int, age: int):
        self._name = name
        self._height = height
        self._age = age

    def get_info(self):
        """Handler for printing plant information"""
        print(f"{self._name}: {self._height}cm, {self._age} days old")


def main():
    """Main"""
    plants: dict[str, Plant] = {}
    plants["Rose"] = Plant("Rose", 25, 30)
    plants["Sunflower"] = Plant("Sunflower", 80, 45)
    plants["Cactus"] = Plant("Cactus", 15, 120)

    print("=== Garden Plant Registry ===")
    for key in plants:
        plants[key].get_info()


if __name__ == "__main__":
    main()
