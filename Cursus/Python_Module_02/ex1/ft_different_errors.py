#!/usr/bin/env python3


def garden_operations(plt: dict, key: str, val: str, file: str, all: bool):
    res: int | None = None
    ival: int | None = None
    if all:
        try:
            ival = int(val)
            open(file)
            height = plt[key]
            res = height // ival
        except (ValueError, ZeroDivisionError, KeyError, FileNotFoundError):
            print("Caught multiple errors")
    else:
        try:
            ival = int(val)
            open(file)
            height = plt[key]
            res = height // ival
        except ValueError:
            print(f"ValueError: '{val}' is not an int")
        except ZeroDivisionError:
            print(f"ZeroDivisionError: Can't divide by '{ival}'")
        except KeyError:
            print("KeyError: Not a valid key")
        except FileNotFoundError:
            print(f"FileNotFoundError: '{file}' is not a valid fd or path")
    return res


def test_error_types():
    plant_heights: dict[str, int] = {"rose": 5}

    print("Testing value error")
    garden_operations(plant_heights, "rose", "abc", "/dev/null", all=False)
    print()

    print("Testing zero devision")
    garden_operations(plant_heights, "rose", "0", "/dev/null", all=False)
    print()

    print("Testing missing key")
    garden_operations(plant_heights, "foo", "2", "/dev/null", all=False)
    print()

    print("Testing file not found")
    garden_operations(plant_heights, "rose", "2", "file.txt", all=False)
    print()

    print("Testing multiple exceptions")
    garden_operations(plant_heights, "rose", "2", "file.txt", all=True)
    print()


if __name__ == "__main__":
    test_error_types()
    print()
    print("This ran after the errors")
