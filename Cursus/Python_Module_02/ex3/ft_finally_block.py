#!/usr/bin/env python3


def water_plants(plant_list: dict[str, int]):
    print("Opening watering system")
    plant_name = None
    try:
        for plant_name in plant_list:
            wather_level = plant_list[plant_name]
            wather_level += 1
            print(f"\tWathering {plant_name}")
        print("\tWatering completed successfully!")
    except Exception:
        print(f"\tError: Cannot wather {plant_name} - invalid plant!")
    finally:
        print("Closing watering system (cleanup)")


def main():
    good_plant_list = {"rose": 0, "cactus": 1, "sunflower": 5}
    bad_plant_list = {"rose": 0, "cactus": "x", "sunflower": 5}

    print("Tesing normal watering...")
    water_plants(good_plant_list)
    print()
    print("Tesing with errors...")
    water_plants(bad_plant_list)


if __name__ == "__main__":
    main()
