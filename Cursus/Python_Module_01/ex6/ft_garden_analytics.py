#!/usr/bin/env python3


class Plant:
    """Plant class"""

    plant_data = {
        "Rose": {"growth_rate": 2, "blooming_age": 1},
        "Tulip": {"growth_rate": 3, "blooming_age": 10},
        "Sunflower": {"growth_rate": 5, "blooming_age": 4},
        "Cactus": {"growth_rate": 1, "blooming_age": 25},
        "Oak": {"growth_rate": 1, "blooming_age": 150},
    }

    def __init__(self, name: str, height: int):
        self.type = "regular"
        self.name = name
        self.height = height
        self.age: int = 0

    def info(self):
        print(f"{self.name}: {self.height}cm")

    def check_height(self) -> bool:
        valid = False
        if self.height > 0:
            valid = True
        return valid


class FloweringPlant(Plant):
    """Flower class"""

    def __init__(self, name: str, height: int, color: str):
        super().__init__(name, height)
        self.type = "flowering"
        self.color = color
        self.blooming = False

    def bloom(self):
        if self.age >= self.plant_data[self.name]["blooming_age"]:
            self.blooming = True

    def info(self):
        print(f"{self.name}: {self.height}cm, {self.color} flowers ", end="")
        self.bloom()
        if self.blooming is True:
            print("(blooming)")
        else:
            print()


class PrizeFlower(FloweringPlant):
    """Prize class"""

    def __init__(self, name: str, height: int, color: str):
        super().__init__(name, height, color)
        self.type = "prize"
        self.prize = 0


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
    def score(plants: dict[str, Plant | FloweringPlant | PrizeFlower]) -> int:
        score = 0
        for pkey in plants:
            plant = plants[pkey]
            score += plant.age + plant.height
        return score

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
                GardenManager.log("Plant type exists.", True)
                return
            self.gardens[garden].plants[plant.name] = plant
            GardenManager.log(f"Added {plant.name} to {garden} garden")
            self.gardens[garden].count += 1
            if plant.type == "flowering":
                self.gardens[garden].flowering += 1
            elif plant.type == "prize":
                self.gardens[garden].prize += 1
            else:
                self.gardens[garden].regular += 1

    def grow(self, garden: str):
        plants = self.gardens[garden].plants
        for pkey in plants:
            plant = plants[pkey]
            plant.age += 1
            plant.height += Plant.plant_data[pkey]["growth_rate"]
        self.log(f"{garden} is growing")

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
        print("Garden scores")
        for key in self.gardens:
            garden = self.gardens[key]
            print(f"    - {garden.name}: {self.score(garden.plants)}")
        print(f"Total gardesns managed: {self.garden_count}")
        print()


def main():
    print("=== Garden Management System Demo ===")
    manager = GardenManager()
    manager.create_garden_network("Alice", "Bob")
    manager.add_plant("X", Plant("Rose", 10))
    manager.add_plant("Alice", Plant("Oak", 101))
    manager.add_plant("Alice", FloweringPlant("Rose", 101, "red"))
    manager.add_plant("Alice", FloweringPlant("Sunflower", 101, "yellow"))
    manager.add_plant("Bob", FloweringPlant("Rose", 101, "yellow"))
    manager.add_plant("Bob", PrizeFlower("Tulip", 15, "black"))
    manager.grow("Alice")
    manager.grow("Alice")
    manager.grow("Alice")
    manager.grow("Bob")
    manager.grow("Bob")
    print()
    manager.report()


if __name__ == "__main__":
    main()
