#!/usr/bin/env python3


class GardenStats:

    def __init__(self) -> None:
        self.name: str | None = None
        self.regular: int
        self.flowering: int
        self.prize: int


class GardenManager:
    max_tokens: int = 4
    used_tokens: int = 0
    session: int | None = None

    def __init__(self) -> None:
        self._gardens: list[GardenStats] = [
            GardenStats(),
            GardenStats(),
            GardenStats(),
            GardenStats(),
        ]

    @staticmethod
    def log(message: str, is_error: bool = False) -> None:
        """Handler for loging messages"""
        status: str = "Info"
        if is_error == 1:
            status = "Error"
        print(f"G:> [ {status:^5} ] {message}")

    def add_garden(self, name: str):
        i = 0
        while i < self.max_tokens:
            if self._gardens[i].name is None:
                self.log(f"'{name}' garden added.")
                self._gardens[i].name = name
                return
            if self._gardens[i].name == name:
                self.log("Name taken.", is_error=True)
                exit()
            i += 1
        if i == 4:
            self.log("Max number of gardens exceeded", is_error=True)
            exit()


class Plant:
    """Plant class"""

    def __init__(self):
        self._name: str
        self._height: int
        self._age: int

    def add(self, name: str, height: int, age: int):
        self._name = name
        self._height = height
        self._age = age


class FloweringPlant(Plant):
    """Flower class"""

    def __init__(self):
        super().__init__()


class PrizeFlower(FloweringPlant):
    """Tree class"""

    def __init__(self):
        super().__init__()


def main():
    print("=== Garden Management System [GMS] ===")
    manager = GardenManager()
    active_seesion = True
    while (active_seesion):
        kb_read = input("G:> ")
        if kb_read == "exit":
            manager.log("Exiting")
            active_seesion = False




if __name__ == "__main__":
    main()
