#!/usr/bin/env python3


class GardenStats:

    def __init__(self, name: str) -> None:
        self.name = name
        self.regular: int
        self.flowering: int
        self.prize: int


class GardenManager:
    max_gardens = 4

    def __init__(self) -> None:
        self._gardens: list[GardenStats | None] = [None, None, None, None]

    def add_garden(self, name: str):
        i = 0
        while i < self.max_gardens:
            if self._gardens[i] is None:
                self._gardens[i] = GardenStats(name)

    def log(self, name):
        pass


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


class FloweringPlant(Plant):
    """Flower class"""

    def __init__(self):
        super().__init__()


class PrizeFlower(FloweringPlant):
    """Tree class"""

    def __init__(self):
        super().__init__()


def main():
    manager = GardenManager()


if __name__ == "__main__":
    main()
