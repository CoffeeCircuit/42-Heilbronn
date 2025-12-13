#!/usr/bin/env python3


class PlantException(Exception):
    def __init__(self, message: str, name: str | None = None) -> None:
        super().__init__(message)
        self.name = name


class Plant:

    def __init__(self, name: str | None, water: int, health: int) -> None:
        self.name = name
        self.water = water
        self.health = health

    @property
    def name(self):
        if self._name is None or self._name == "":
            msg = f"Plant '{self._name}': Invalid name"
            raise PlantException(msg, name=self._name)
        return self._name

    @name.setter
    def name(self, name: str | None):
        if name is None or name == "":
            msg = f"Plant '{name}': Invalid name"
            raise PlantException(msg, name=name)
        self._name = name

    @property
    def water(self):
        if self._water < 0:
            msg = f"Plant '{self._name}': Negative water value '{self._water}'"
            raise PlantException(msg, name=self._name)
        return self._water

    @water.setter
    def water(self, water: int):
        if water < 0:
            msg = f"Plant '{self._name}': Negative water value '{water}'"
            raise PlantException(msg, name=self._name)
        self._water = water

    @property
    def health(self):
        if self._health < 0:
            _health = self._health
            msg = f"Plant '{self._name}': Negative health value '{_health}'"
            raise PlantException(msg, name=self._name)
        return self._health

    @health.setter
    def health(self, health: int):
        if health < 0:
            msg = f"Plant '{self._name}': Negative health value '{health}'"
            raise PlantException(msg, name=self._name)
        self._health = health


class GardenManager:

    def __init__(self) -> None:
        self.plants: dict[str, Plant] = {}

    def add_plant(self, name: str | None, water: int, health: int):
        try:
            plant = Plant(name, water, health)
            self.plants[plant.name] = plant
            print(f"Plant '{plant.name}' added successfully")
        except PlantException as e:
            print("Error:", e)


def main():
    print("=== Garden Management System ===")
    manager = GardenManager()
    manager.add_plant("Rose", 5, 10)
    manager.add_plant("Tomato", 10, 12)
    manager.add_plant("Lettuce", 1, 2)

    # error testing
    manager.add_plant(None, 5, 10)
    manager.add_plant("", 5, 10)
    manager.add_plant("Foo", -5, 10)
    manager.add_plant("Bar", 5, -10)


if __name__ == "__main__":
    main()
