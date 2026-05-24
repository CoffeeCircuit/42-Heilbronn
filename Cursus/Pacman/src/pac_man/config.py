import json

from pydantic import BaseModel, ConfigDict, model_validator
from typing_extensions import Self

_CLAMPS: list[tuple[str, int]] = [
    ("width", 5),
    ("height", 5),
    ("lives", 1),
    ("pacgum", 1),
    ("points_per_pacgum", 1),
    ("points_per_super_pacgum", 1),
    ("points_per_ghost", 1),
    ("level_max_time", 10),
]


def _strip_comments(text: str) -> str:
    return "\n".join(
        line for line in text.split("\n")
        if not line.lstrip().startswith(("#", "//"))
    )


class ConfigData(BaseModel):
    model_config = ConfigDict(extra="ignore")

    highscore_filename: str = "highscore.json"
    width: int = 14
    height: int = 18
    lives: int = 3
    pacgum: int = 42
    points_per_pacgum: int = 10
    points_per_super_pacgum: int = 50
    points_per_ghost: int = 200
    seed: int = 42
    level_max_time: int = 90

    @model_validator(mode="after")  # type: ignore[arg-type]
    def _clamp_values(self) -> Self:
        for name, minimum in _CLAMPS:
            value = getattr(self, name)
            if value < minimum:
                print(f"Warning: clamping {name} from {value} to {minimum}")
                object.__setattr__(self, name, minimum)
        return self


class Config:
    def __init__(self) -> None:
        self.data: ConfigData

    def read(self, file: str) -> bool:
        """Load and validate config file. Returns True on success."""
        try:
            with open(file) as fp:
                raw = fp.read()
            parsed = json.loads(_strip_comments(raw))
            self.data = ConfigData(**parsed)
            return True
        except FileNotFoundError:
            print(f"Error: Config file '{file}' not found")
            return False
        except json.JSONDecodeError as e:
            print(f"Error: Invalid JSON in '{file}': {e}")
            return False
        except Exception as e:
            print(f"Error: Invalid config - {e}")
            return False

    @property
    def width(self) -> int:
        return self.data.width

    @property
    def height(self) -> int:
        return self.data.height

    @property
    def seed(self) -> int:
        return self.data.seed

    @property
    def lives(self) -> int:
        return self.data.lives

    @property
    def highscore_filename(self) -> str:
        return self.data.highscore_filename

    @property
    def pacgum(self) -> int:
        return self.data.pacgum

    @property
    def points_per_pacgum(self) -> int:
        return self.data.points_per_pacgum

    @property
    def points_per_super_pacgum(self) -> int:
        return self.data.points_per_super_pacgum

    @property
    def points_per_ghost(self) -> int:
        return self.data.points_per_ghost

    @property
    def level_max_time(self) -> int:
        return self.data.level_max_time
