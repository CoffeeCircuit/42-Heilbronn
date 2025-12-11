#!/usr/bin/env python3


class Plant:
    """Plant class"""

    plant_data = {"Rose": {"growth": 1}}

    def __init__(self, name: str, height: int, age: int):
        self.name = name
        self.height = height
        self.age = age


class FloweringPlant(Plant):
    """Flower class"""

    def __init__(self, name: str, height: int, age: int):
        super().__init__(name, height, age)


class PrizeFlower(FloweringPlant):
    """Tree class"""

    def __init__(self, name: str, height: int, age: int):
        super().__init__(name, height, age)


class GardenManager:
    garden_count = 0

    def __init__(self) -> None:
        self.gardens: dict[str, GardenManager.GardenStats] = {}

    class GardenStats:
        plant_count = 0

        def __init__(self, name: str) -> None:
            self.name = name
            self.plants: dict[str, Plant] = {}
            self.regular: int
            self.flowering: int
            self.prize: int

    @classmethod
    def _new_garden(cls, name: str) -> GardenStats:
        return cls.GardenStats(name)

    @staticmethod
    def exists(value: str, keys: dict) -> bool:
        existing = False
        for key in keys:
            if key == value:
                existing = True
        return existing

    @staticmethod
    def log(msg: str, is_serror: bool = False):
        if is_serror:
            print(f"[ Manager Error ] {msg}")
        else:
            print(f"[ Manager Info  ] {msg}")

    def list_gardens(self) -> None:
        print("Existing gardens: ", end="")
        for key in self.gardens:
            print(key, end=", ")
        print()

    def add_garden(self, *names: str):
        """Handler to add new garden instance
        Note! Takes a variable number of arguments
        """
        for name in names:
            self.gardens[name] = self._new_garden(name)
            GardenManager.garden_count += 1

    def add_plant(self, garden: str, plant: Plant):
        if not GardenManager.exists(garden, self.gardens):
            GardenManager.log(f"No {garden} garden exists", True)
            return
        else:
            if GardenManager.exists(plant.name, self.gardens[garden].plants):
                GardenManager.log("Plant type exists. Use update", True)
                return
            self.gardens[garden].plants[plant.name] = plant
            GardenManager.log(f"Added {plant.name} to {garden} garden")
            self.gardens[garden].plant_count += 1

    def update(self):
        pass

    def report(self, garden: str):
        pass


def main():
    manager = GardenManager()
    manager.add_garden("Alice")
    manager.add_garden("Bob")
    manager.add_garden("Mike", "Ross")
    manager.list_gardens()
    print("Garden count: ", manager.garden_count)

    manager.add_plant("Alice", Plant("Rose", 10, 5))
    manager.add_plant("X", Plant("Rose", 10, 5))
    manager.add_plant("Alice", Plant("Rose", 10, 5))
    manager.add_plant("Bob", Plant("Rose", 10, 5))


if __name__ == "__main__":
    main()
