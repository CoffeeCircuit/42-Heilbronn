#!/usr/bin/env python3


class SecurePlant:
    """Secure plant class"""

    def __init__(self):
        self._name: str | None = None
        self._height: int | None = None
        self._age: int | None = None

    @property
    def height(sefl):
        return sefl._height

    @property
    def age(sefl):
        return sefl._age

    @height.setter
    def height(self, value: int):
        if value < 0:
            print(f"Invalid height: {value}cm [REJECTED]")
        else:
            self._height = value
            print(f"Height updated: {value} days [OK]")

    @age.setter
    def age(self, value: int):
        if value < 0:
            print(f"Invalid age: {value} [REJECTED]")
        else:
            self._age = value
            print(f"Age updated: {value} days [OK]")


def main():
    plant = SecurePlant()
    plant.height = 30
    plant.age = 3
    plant._age = -3


if __name__ == "__main__":
    main()
