#!/usr/bin/env python3


class GardenError(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


class PlantError(GardenError):
    def __init__(self, *args: object, health) -> None:
        if health < 2:
            super().__init__("Health error")
        else:
            super().__init__(*args)
        self._health = health


class WaterError(GardenError):
    def __init__(self, *args: object, water) -> None:
        super().__init__(*args)
        self.water = water


def main():
    print("=== Custom Garden Errors ===")

    print()
    print("Testing GardenError")
    try:
        raise GardenError("From GardenError")
    except GardenError as e:
        print("Error: ", e)

    print()
    print("Testing PlantError")
    try:
        raise PlantError("Initial PlantError", health=1)
    except PlantError as e:
        print("Error: ", e)

    print()
    print("Testing WaterError")
    try:
        raise WaterError("From WaterError", water=-5)
    except WaterError as e:
        print("Error: ", e)
        print("\tWather level: ", e.water)


if __name__ == "__main__":
    main()
