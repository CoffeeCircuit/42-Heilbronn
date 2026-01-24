"""
Exercise 0: Space Station Data
Directory: ex0/
Files to Submit: space_station.py
Authorized: None
"""

from importlib.metadata import version, PackageNotFoundError

try:
    pydantic_version: str | None = version("pydantic")
except PackageNotFoundError:
    pydantic_version = None

if not pydantic_version or not pydantic_version.startswith("2."):
    print("Pydantic v2 is required for this exercise.")
    print("Run:")
    print("uv venv")
    print("uv pip install pydantic==2.0")
    print("uv run ex0/space_station.py")
    exit(1)

from pydantic import BaseModel, Field  # type: ignore
from pydantic import ValidationError  # type: ignore
from pydantic import AwareDatetime  # type: ignore
from datetime import datetime


class SpaceStation(BaseModel):
    station_id: str = Field(min_length=3, max_length=10)
    name: str = Field(min_length=1, max_length=50)
    crew_size: int = Field(ge=1, le=20)
    power_level: float = Field(ge=0.0, le=100.0)
    oxygen_level: float = Field(ge=0.0, le=100.0)
    last_maintenance: AwareDatetime
    is_operational: bool = Field(default=True)
    notes: str | None = Field(default=None, max_length=200)


def main():
    print("Space Station Data Validation")
    print("========================================")
    print("Valid station created")
    try:
        station = SpaceStation(
            station_id="ISS001",
            name="International Space Station",
            crew_size=18,
            power_level=95.5,
            oxygen_level=98.0,
            last_maintenance=datetime(2023, 5, 15, 10, 0, 0).astimezone(),
            is_operational=True,
            notes="All systems nominal.",
        )
        print(
            *(f"{k}: {v}" for k, v in station.model_dump().items()),
            sep="\n",
        )
    except ValidationError as e:
        print(e.errors()[0]["msg"])

    print("\n========================================")
    print("Expected validation error")
    try:
        station = SpaceStation(
            station_id="ISS001",
            name="International Space Station",
            crew_size=30,  # Invalid crew size
            power_level=95.5,
            oxygen_level=98.0,
            last_maintenance=datetime(2023, 5, 15, 10, 0, 0).astimezone(),
            is_operational=True,
            notes="All systems nominal.",
        )
        print(
            *(f"{k}: {v}" for k, v in station.model_dump().items()),
            sep="\n",
        )
    except ValidationError as e:
        print(e.errors()[0]["msg"])


if __name__ == "__main__":
    main()
