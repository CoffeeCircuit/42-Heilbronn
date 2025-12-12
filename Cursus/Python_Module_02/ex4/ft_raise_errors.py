#!/usr/bin/env python3


def check_plant_health(plant_name: str, water_level: int, sunlight_hours: int):
    if plant_name == "":
        raise ValueError("Error: Missing name")
    elif water_level > 10 or water_level < 1:
        raise ValueError("Error: Water level is not OK")
    elif sunlight_hours > 12 or sunlight_hours < 2:
        raise ValueError("Error: Sunlight hours are not OK")
    else:
        print("Info : OK")


def test_plant_checks():
    print("Testing case 1: (good test)")
    check_plant_health("rose", 9, 6)
    print()

    print("Testing case 2: (name fail)")

    try:
        check_plant_health("", 9, 6)
    except ValueError as e:
        print(e)
    print()

    print("Testing case 3: (water_level fail)")
    try:
        check_plant_health("rose", 11, 6)
    except ValueError as e:
        print(e)
    print()

    print("Testing case 4: (sunlight_hourrs fail)")
    try:
        check_plant_health("rose", 5, 1)
    except ValueError as e:
        print(e)
    print()


if __name__ == "__main__":
    test_plant_checks()
