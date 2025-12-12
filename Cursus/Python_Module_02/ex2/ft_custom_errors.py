#!/usr/bin/env python3


class GardenError(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


class PlantError(GardenError):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


class WaterError(GardenError):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


def main():
    pass


if __name__ == "__main__":
    main()
