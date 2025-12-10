#!/usr/bin/env python3


class Plant:
    """Plant class"""

    def __init__(self):
        self._name: str
        self._height: int
        self._age: int

    def add(self, name: str, height: int, age: int):
        self._name = name
        self._height = height
        self._age = age


def plant_info(plant: Plant):
    """Handler for printing plant information"""
    print(f"{plant._name}: {plant._height}cm, {plant._age} days old")


def main():
    """Main"""
    plant1 = Plant()
    plant2 = Plant()
    plant3 = Plant()
    plant1.add(name="Rose", height=25, age=30)
    plant2.add(name="Sunflower", height=80, age=45)
    plant3.add(name="Cactus", height=15, age=120)
    print("=== Garden Plant Registry ===")
    plant_info(plant1)
    plant_info(plant2)
    plant_info(plant3)


if __name__ == "__main__":
    main()
