#!/usr/bin/env python3


class Plant:
    """Plant class"""

    def __init__(self, name: str, height: int, age: int):
        self._name = name
        self._height = height
        self._age = age


class FloweringPlant(Plant):
    """Flower class"""

    def __init__(self, name: str, height: int, age: int):
        super().__init__(name, height, age)


class PrizeFlower(FloweringPlant):
    """Tree class"""

    def __init__(self, name: str, height: int, age: int):
        super().__init__(name, height, age)


class GardenManager:
    count = 0

    class GardenStats:

        def __init__(self, name: str) -> None:
            self.name = name
            self.plants: dict[str, Plant] = {}
            self.regular: int
            self.flowering: int
            self.prize: int

    @classmethod
    def _new_garden(cls, name: str) -> GardenStats:
        return cls.GardenStats(name)

    def __init__(self) -> None:
        self.gardens: dict[str, GardenManager.GardenStats] = {}

    def add_garden(self, *names: str):
        for name in names:
            self.gardens[name] = self._new_garden(name)
            GardenManager.count += 1

    def show_gardens(self):
        print("Existing gardens: ", end="")
        for key in self.gardens:
            print(key, end=", ")
        print()


def main():
    manager = GardenManager()
    manager.add_garden("Alice")
    manager.add_garden("Bob")
    manager.add_garden("Mike", "Ross")

    manager.show_gardens()

    print(manager.count)

    print(manager.gardens["Alice"])


if __name__ == "__main__":
    main()
