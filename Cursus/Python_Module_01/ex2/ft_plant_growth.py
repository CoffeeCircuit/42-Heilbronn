#!/usr/bin/env python3


class Plant:
    """Plant class"""

    plants_growth_rate: dict[str, int] = {
        "Rose": 2,
        "Sunflower": 5,
        "Cactus": 1,
    }

    def __init__(self):
        self._name: str
        self._height: int
        self._age: int

    def add(self, name: str, height: int, age: int):
        self._name = name
        self._height = height
        self._age = age

    def grow(self):
        """Handler for growing the plant."""
        self._height += self.plants_growth_rate[self._name]

    def age(self):
        """Handler for aging the plant."""
        self._age += 1

    def get_info(self):
        """Handler for printing plant information"""
        print(f"{self._name}: {self._height}cm, {self._age} days old")


def simulate_growth(plant: Plant):
    """Simulate one week of growth for a perticular plant"""
    c_day = 1
    height = plant._height
    print(f"=== Day {c_day} ===")
    plant.get_info()
    while c_day < 7:
        plant.grow()
        plant.age()
        c_day += 1
    print(f"=== Day {c_day} ===")
    plant.get_info()
    print(f"Growth this week: +{plant._height - height}cm")


def main():
    """Main"""
    plant1 = Plant()
    plant2 = Plant()
    plant3 = Plant()
    plant1.add(name="Rose", height=25, age=30)
    plant2.add(name="Sunflower", height=80, age=45)
    plant3.add(name="Cactus", height=15, age=120)
    simulate_growth(plant1)
    print()
    simulate_growth(plant2)
    print()
    simulate_growth(plant3)
    print()


if __name__ == "__main__":
    main()
