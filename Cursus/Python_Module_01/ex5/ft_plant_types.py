#!/usr/bin/env python3


class Plant:
    """Plant class"""

    def __init__(self, name, height, age):
        self._name = name
        self._height = height
        self._age = age

    def get_info(self):
        """Handler for printing plant information"""
        print(f"{self._name}: {self._height}cm, {self._age} days old")


class Flower(Plant):
    """Flower class"""

    def __init__(self, name, height, age, color):
        super().__init__(name, height, age)
        self._color = color

    def bloom(self):
        pass

    def get_info(self):
        print(f"{self._name} (Flower): {self._height}cm, ", end="")
        print(f"{self._age} days, {self._color} color")


class Tree(Plant):
    """Tree class"""

    def __init__(self, name, height, age, trunk_diameter: int):
        super().__init__(name, height, age)
        self._trunk_diameter = trunk_diameter

    def produce_shade(self):
        pass

    def get_info(self):
        print(f"{self._name} (Tree): {self._height}cm, ", end="")
        print(f"{self._age} days, {self._trunk_diameter}cm diameter")


class Vegetable(Plant):
    """Vegetable class"""

    def __init__(self, name, height, age, harvest_season, nutritional_value):
        super().__init__(name, height, age)
        self._harvest_season = harvest_season
        self._nutritional_value = nutritional_value

    def get_info(self):
        print(f"{self._name} (Vegetable): {self._height}cm, ", end="")
        print(f"{self._age} days, {self._harvest_season}")
        print(f"{self._name} is {self._nutritional_value}")


def main():
    print("=== Garden Plant Types ===")

    plants: dict[str, Plant | Flower | Tree | Vegetable] = {
        "rose": Flower("Rose", 25, 30, "red"),
        "oak": Tree("Oak", 500, 1825, 50),
        "tomato": Vegetable("Tomato", 80, 90, "summer", "rich in vitamin C"),
    }

    for key in plants:
        plants[key].get_info()


if __name__ == "__main__":
    main()
