"""
pace Crew Management
Directory: ex2/
Files to Submit: space_crew.py
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
    print("uv run ex2/space_crew.py")
    exit(1)


from pydantic import BaseModel, Field, model_validator  # type: ignore
from pydantic import ValidationError  # type: ignore
from pydantic import AwareDatetime  # type: ignore
from enum import IntFlag, auto
from datetime import datetime


class RankEnum(IntFlag):
    cadet = auto()
    officer = auto()
    liutenant = auto()
    captain = auto()
    commander = auto()


class CrewMember(BaseModel):
    member_id: str = Field(min_length=3, max_length=10)
    name: str = Field(min_length=2, max_length=50)
    rank: RankEnum = Field()
    age: int = Field(ge=18, le=80)
    specialization: str = Field(min_length=3, max_length=30)
    years_experience: int = Field(ge=0, le=50)
    is_active: bool = Field(default=True)


class SpaceMission(BaseModel):
    mission_id: str = Field(min_length=5, max_length=15)
    mission_name: str = Field(min_length=3, max_length=100)
    destination: str = Field(min_length=3, max_length=50)
    launch_date: AwareDatetime
    duration_days: int = Field(ge=1, le=3650)
    crew: list[CrewMember] = Field(min_length=1, max_length=12)
    mission_status: str = Field(default="planned")
    budget_millions: float = Field(ge=1.0, le=10000.0)

    @model_validator(mode="after")  # type: ignore
    def validate_mission(self) -> "SpaceMission":
        if not self.mission_id.startswith("M"):
            raise ValueError('Mission ID must start with "M" (Mission)')

        if not any(
            member.rank in (RankEnum.commander, RankEnum.captain)
            for member in self.crew
        ):
            msg = "Mission must have at least one Commander or Captain"
            raise ValueError(msg)

        if (
            self.duration_days > 365
            and len(list(filter(lambda m: m.years_experience > 5, self.crew)))
            < len(self.crew) * 0.5
        ):
            raise ValueError(
                "Long missions (> 365 days) require at least half the crew "
                "to have more than 5 years of experience"
            )

        if not all(member.is_active for member in self.crew):
            raise ValueError("All crew members must be active for the mission")

        return self


def space_crew():
    print("Space Mission Crew Validation")
    print("=" * 41)
    print("Valid mission created:")

    try:
        mission = SpaceMission(
            mission_id="M2024_MARS",
            mission_name="Mars Colony Establishment",
            destination="Mars",
            launch_date=datetime(2024, 7, 1, 9, 0, 0).astimezone(),
            duration_days=900,
            budget_millions=2500.0,
            crew=[
                CrewMember(
                    member_id="CM001",
                    name="Sarah Connor",
                    rank=RankEnum.commander,
                    age=45,
                    specialization="Mission Command",
                    years_experience=20,
                    is_active=True,
                ),
                CrewMember(
                    member_id="CM002",
                    name="John Smith",
                    rank=RankEnum.liutenant,
                    age=38,
                    specialization="Navigation",
                    years_experience=12,
                    is_active=True,
                ),
                CrewMember(
                    member_id="CM003",
                    name="Alice Johnson",
                    rank=RankEnum.officer,
                    age=32,
                    specialization="Engineering",
                    years_experience=8,
                    is_active=True,
                ),
            ],
            mission_status="planned",
        )
        print(f"Mission: {mission.mission_name}")
        print(f"ID: {mission.mission_id}")
        print(f"Destination: {mission.destination}")
        print(f"Duration: {mission.duration_days} days")
        print(f"Budget: ${mission.budget_millions}M")
        print(f"Crew size: {len(mission.crew)}")
        print("Crew members:")
        for member in mission.crew:
            print(
                f"- {member.name} ({member.rank.name})",
                f"- {member.specialization}",
            )
    except ValidationError as e:
        print(e.errors()[0]["msg"])

    print("=" * 41)
    print("Expected validation error:")

    try:
        mission = SpaceMission(
            mission_id="M2024_MOON",
            mission_name="Lunar Base Setup",
            destination="Moon",
            launch_date=datetime(2024, 8, 1, 9, 0, 0).astimezone(),
            duration_days=180,
            budget_millions=500.0,
            crew=[
                CrewMember(
                    member_id="CM004",
                    name="Bob Wilson",
                    rank=RankEnum.officer,
                    age=35,
                    specialization="Engineering",
                    years_experience=10,
                    is_active=True,
                ),
                CrewMember(
                    member_id="CM005",
                    name="Jane Doe",
                    rank=RankEnum.liutenant,
                    age=40,
                    specialization="Science",
                    years_experience=15,
                    is_active=True,
                ),
            ],
            mission_status="planned",
        )
        print(f"Mission: {mission.mission_name}")
    except ValidationError as e:
        print(e.errors()[0]["msg"])


if __name__ == "__main__":
    space_crew()
