#!/usr/bin/env python3


class PlantException(Exception):
    def __init__(self, *args: object, name: str | None) -> None:
        super().__init__(*args)
        self.name = name


class Plant:

    def __init__(self, name: str | None, water: int, health: int) -> None:
        self._name = name
        self._water = water
        self._health = health

    @property
    def name(self):
        if self._name is None:
            raise PlantException("Plant name cannot be None", name=self._name)
        return self._name

    @name.setter
    def name(self, name: str):
        if name is None:
            raise PlantException("Plant name cannot be None", name=self._name)
        self._name = name


class GardenManager:

    def __init__(self) -> None:
        self.plants: dict[str, Plant] = {}

    def add_plant(self, plant: Plant):
        try:
            self.plants[plant.name] = plant
            print(f"Pland {plant.name} added")
        except PlantException as e:
            print("Error:", e)

    def water_plans(self):
        pass

    def check_health(self):
        pass


def main():
    manager = GardenManager()
    manager.add_plant(Plant("Rose", 5, 10))
    manager.add_plant(Plant(None, 5, 10))


if __name__ == "__main__":
    main()
