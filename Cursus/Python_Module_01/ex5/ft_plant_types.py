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


class Flower(Plant):
    """Flower class"""

    def __init__(self):
        super().__init__()
        self.color: str

    def bloom(self):
        pass


class Tree(Plant):
    """Tree class"""

    def __init__(self):
        super().__init__()
        self.trunk_diameter: str

    def produce_shade(self):
        pass


class Vegetable(Plant):
    """Vegetable class"""

    def __init__(self):
        super().__init__()
        self.harvest_season: str
        self.nutritional_value: str


def main():
    pass


if __name__ == "__main__":
    main()
