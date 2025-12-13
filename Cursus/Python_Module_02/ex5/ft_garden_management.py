#!/usr/bin/env python3


class PlantException(Exception):
    def __init__(self, message: str, name: str | None = None) -> None:
        super().__init__(message)
        self.name = name


class GardenException(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


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
        msg: str | None = None
        if water < 0:
            msg = f"Plant '{self._name}': Negative water value '{water}'"
            raise PlantException(msg, name=self._name)
        if water > 10:
            msg = f"Plant '{self._name}': High water level '{water}'"
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
    tank = 3

    def __init__(self) -> None:
        self.plants: dict[str, Plant] = {}

    def add_plant(self, name: str | None, water: int, health: int):
        try:
            plant = Plant(name, water, health)
            self.plants[plant.name] = plant
            print(f"Plant '{plant.name}' added successfully")
        except PlantException as e:
            print("Error:", e)

    def water_plants(self):
        plant_list = self.plants
        plant_name = None
        print("Opening watering system")
        for plant_name in plant_list:
            try:
                plant_list[plant_name].water += 1
                print(f"\tWathering {plant_name}")
            except PlantException as e:
                print("Error:", e)
        print("Closing watering system (cleanup)")

    def check_health(self):
        plant_list = self.plants
        pname = None
        print("Checking plant health")
        try:
            for pname in plant_list:
                if plant_list[pname].health < 2:
                    msg = f"Plant '{pname}': Low health"
                    raise PlantException(msg, name=pname)
                print(f"\tChecking {pname}")
        except PlantException as e:
            print("Error:", e)

    def test_system(self):
        print("Testing error recovery...")
        try:
            if self.tank < 4:
                msg = "Not enough water in tank"
                raise GardenException(msg)
        except GardenException as e:
            print("Error:", e)
        finally:
            print("System recovered and continuing...")
        print()
        print("Garden management system test complete!")


def main():
    print("=== Garden Management System ===")
    print()
    manager = GardenManager()
    manager.add_plant("Rose", 5, 5)
    manager.add_plant("Tomato", 9, 9)
    manager.add_plant("Lettuce", 10, 4)
    manager.add_plant("Sunflower", 3, 1)

    # error testing
    print()
    manager.add_plant(None, 5, 2)
    manager.add_plant("", 5, 3)
    manager.add_plant("Foo", -5, 2)
    manager.add_plant("Bar", 5, -2)

    # testing functionality
    print()
    manager.water_plants()
    print()
    manager.check_health()
    print()
    manager.test_system()


if __name__ == "__main__":
    main()
