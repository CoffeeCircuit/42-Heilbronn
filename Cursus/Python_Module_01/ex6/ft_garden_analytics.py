#!/usr/bin/env python3


class Plant:
    """Plant class"""

    plant_data = {"Rose": {"growth_rate": 1, "blooming_age": 20}}

    def __init__(self, name: str, height: int, age: int):
        self.name = name
        self.height = height
        self.age = age

    def info(self):
        print(f"{self.name}: {self.height}cm")

    def check_height(self) -> bool:
        valid = False
        if self.height > 0:
            valid = True
        return valid


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
        def __init__(self, name: str) -> None:
            self.name = name
            self.count: int = 0
            self.growth: int = 0
            self.plants: dict[str, Plant] = {}
            self.regular: int = 0
            self.flowering: int = 0
            self.prize: int = 0

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
            print(f"[ Garden Error ] {msg}")
        else:
            print(f"[ Garden Info  ] {msg}")

    def list_gardens(self) -> None:
        print("Existing gardens: ", end="")
        for key in self.gardens:
            print(key, end=", ")
        print()

    def create_garden_network(self, *names: str):
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
            self.gardens[garden].count += 1

    def update(self):
        pass

    def validate_height(self):
        valid = True
        for garden in self.gardens:
            plants = self.gardens[garden].plants
            for pkey in plants:
                if plants[pkey].check_height() is False:
                    valid = False
        return valid

    def report(self):
        """Prints a report of existing (or specific) garden(s)"""
        for key in self.gardens:
            garden = self.gardens[key]
            plants = garden.plants
            print(f"=== {garden.name}'s Garden Report ===")
            print("    Plants in garden:")
            for pkey in plants:
                print("\t- ", end="")
                plants[pkey].info()
            print()
            print(f"    Plants added: {garden.count}, ", end="")
            print(f"Total growth: {garden.growth}")
            print(f"    Plant types: {garden.regular} regular, ", end="")
            print(f"{garden.flowering} flowering, ", end="")
            print(f"{garden.prize} prize flowers")
            print()
        print(f"Height validation test: {self.validate_height()}")

        print("Garden scores -:", end="")

        print(f"Total gardesns managed: {self.garden_count}")
        print()


def main():
    print("=== Garden Management System Demo ===")
    manager = GardenManager()
    manager.create_garden_network("Alice", "Bob")

    manager.add_plant("Alice", Plant("Rose", 10, 5))
    manager.add_plant("Alice", Plant("Sunflower", 51, 30))
    manager.add_plant("Bob", Plant("Rose", 3, 1))
    manager.add_plant("X", Plant("Rose", 10, 5))
    print()
    manager.report()


if __name__ == "__main__":
    main()
