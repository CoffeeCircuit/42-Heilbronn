#!/usr/bin/env python3


def check_temperature(tem_str: str) -> int | None:
    """"Function check if temperature is between [0, 40) degrees"""
    temp: int | None = None
    try:
        temp = int(tem_str)
        if 0 <= temp < 40:
            print(f"{tem_str}°C is perfect for plants")
        elif temp < 0:
            temp = None
            print(f"{tem_str}°C is too cold for plants")
        else:
            temp = None
            print(f"{tem_str}°C is too hot for plants")
    except ValueError:
        print(f"'{tem_str}' is not a valid number")
    return temp


def main():
    print("return = ", check_temperature("25"))
    print()
    print("return = ", check_temperature("abc"))
    print()
    print("return = ", check_temperature("100"))
    print()
    print("return = ", check_temperature("-50"))
    print()
    print("return = ", check_temperature(""))
    print()


if __name__ == "__main__":
    main()
