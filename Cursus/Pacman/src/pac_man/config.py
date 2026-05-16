import json
from pydantic import BaseModel, ValidationError
from typing import Optional
from . import constants as const


class ConfigData(BaseModel):
    width: int
    height: int
    seed: int


class Config:
    def __init__(self) -> None:
        self.data: ConfigData

    def read(self, file: str) -> bool:
        """
        Load and validate config.
        Returns True on success, False on error.
        """
        try:
            with open(file) as fp:
                raw = json.load(fp)
            self.data = ConfigData(**raw)  # Pydantic validates automatically
            return True
        except FileNotFoundError:
            print(f"Error: Config file '{file}' not found")
            return False
        except ValidationError as e:
            print(f"Error: Invalid config - {e}")
            return False
        except json.JSONDecodeError:
            print(f"Error: '{file}' is not valid JSON")
            return False

    @property
    def width(self):
        return self.data.width

    @property
    def height(self):
        return self.data.height

    @property
    def seed(self):
        return self.data.seed if self.data else 42
