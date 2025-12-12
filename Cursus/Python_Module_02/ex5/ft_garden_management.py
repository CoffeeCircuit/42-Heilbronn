#!/usr/bin/env python3


class PlantException(Exception):
    def __init__(self, *args: object, name, water, health) -> None:
        super().__init__(*args)
        self.name = name
        self.water = water
        self.health = health


class Plant:

    def __init__(self, name: str, water: int, health: int) -> None:
        self._name = name
        self._water = water
        self._health = health


class GardenManager:

    def __init__(self) -> None:
        self.plants: dict[str, Plant]

    def add_plant(self, plant: Plant):
        try:
            self.plants[plant._name] = plant
        except PlantException as e_plant:
            print("Error")

    def water_plans(self):
        pass

    def check_health(self):
        pass


def main():
    manager = GardenManager()
    manager.add_plant(Plant("Rose", 5, 10))


if __name__ == "__main__":
    main()
