from abc import ABC, abstractmethod


class GameStrategy(ABC):
    """Abstract strategy defining how to execute game turns."""

    def __init__(self) -> None:
        """Initialize the strategy with default name."""
        super().__init__()
        self.name: str = "Abstract Strategy"

    @abstractmethod
    def execute_turn(self, hand: list, battlefield: list) -> dict:
        """Execute a game turn with given hand and battlefield state."""
        pass

    @abstractmethod
    def get_strategy_name(self) -> str:
        """Return the name of this strategy."""
        pass

    @abstractmethod
    def prioritize_targets(self, available_targets: list) -> list:
        """Sort and return targets in priority order for attacking."""
        pass
