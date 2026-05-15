from pydantic import BaseModel, ValidationError
from typing import Optional
import json


class ConfigData(BaseModel):
    width: int
    height: int


class Config:
    def __init__(self) -> None:
        self.data: Optional[ConfigData] = None

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
        return self.data.width if self.data else None

    @property
    def height(self):
        return self.data.height if self.data else None
