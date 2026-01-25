from abc import ABC, abstractmethod
from ex0 import Card


class CardFactory(ABC):
    """Abstract factory for creating themed card game objects."""

    @abstractmethod
    def create_creature(self, name_or_power: str | int | None = None) -> Card:
        """Create a creature card with optional name or power."""
        pass

    @abstractmethod
    def create_spell(self, name_or_power: str | int | None = None) -> Card:
        """Create a spell card with optional name or power."""
        pass

    @abstractmethod
    def create_artifact(self, name_or_power: str | int | None = None) -> Card:
        """Create an artifact card with optional name or durability."""
        pass

    @abstractmethod
    def create_themed_deck(self, size: int) -> dict:
        """Create a complete themed deck of specified size."""
        pass

    @abstractmethod
    def get_supported_types(self) -> dict:
        """Return all supported card types for this factory."""
        pass
