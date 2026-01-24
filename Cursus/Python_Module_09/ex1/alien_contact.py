"""
Exercise 1: Alien Contact Logs
Directory: ex1/
Files to Submit: alien_contact.py
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
    print("uv run ex1/alien_contact.py")
    exit(1)


from pydantic import BaseModel, Field, model_validator  # type: ignore
from pydantic import ValidationError  # type: ignore
from pydantic import AwareDatetime  # type: ignore
from enum import IntFlag, auto


class ContactType(IntFlag):
    radio = auto()
    visual = auto()
    physical = auto()
    telepathic = auto()


class AlienContactLog(BaseModel):
    contact_id: str = Field(min_length=5, max_length=15)
    timestamp: AwareDatetime | str
    location: str = Field(min_length=3, max_length=100)
    contact_type: ContactType
    signal_strength: float = Field(ge=0.0, le=10.0)
    duration_minutes: int = Field(ge=1, le=1440)
    witness_count: int = Field(ge=1, le=100)
    message_received: str | None = Field(default=None, max_length=500)
    is_verified: bool = Field(default=False)

    @model_validator(mode="after")  # type: ignore
    def validate_business_rules(self) -> "AlienContactLog":
        con_type = self.contact_type
        if not self.contact_id.startswith("AC"):
            raise ValueError('Contact ID must start with "AC" (Alien Contact)')

        if ContactType.physical in con_type and not self.is_verified:
            raise ValueError("Physical contact reports must be verified")

        if ContactType.telepathic in con_type and self.witness_count < 3:
            raise ValueError("Telepathic contact requires min 3 witnesses")

        if self.signal_strength > 7.0 and not self.message_received:
            raise ValueError("Strong signals (> 7.0) should received message")

        return self


def alien_contact():
    print("Alien Contact Log Validation")
    print("=" * 38)
    print("Valid contact report:")

    try:
        contact = AlienContactLog(
            contact_id="AC_2024_001",
            timestamp="2024-01-15T10:30:00Z",
            location="Area 51, Nevada",
            contact_type=ContactType.radio,
            signal_strength=8.5,
            duration_minutes=45,
            witness_count=5,
            message_received="Greetings from Zeta Reticuli",
            is_verified=True,
        )
        print(
            *(f"{k}: {v}" for k, v in contact.model_dump().items()),
            sep="\n",
        )
    except ValidationError as e:
        print(e.errors()[0]["msg"])

    print("\n", "=" * 38)
    print("Expected validation error:")

    try:
        contact = AlienContactLog(
            contact_id="AC_2024_002",
            timestamp="2024-06-16T03:15:00Z",
            location="Roswell, New Mexico",
            contact_type=ContactType.telepathic,
            signal_strength=6.5,
            duration_minutes=30,
            witness_count=2,  # Less than 3 witnesses
            message_received="Telepathic transmission detected",
            is_verified=False,
        )
        print(f"ID: {contact.contact_id}")
    except ValidationError as e:
        print(e.errors()[0]["msg"])


if __name__ == "__main__":
    alien_contact()
