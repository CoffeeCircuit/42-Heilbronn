# GameEngine.py - Game orchestrator:
# • Method: configure_engine(factory, strategy)
# • Method: simulate_turn()
# • Method: get_engine_status(

from ex0.Card import Card
from ex3.CardFactory import CardFactory
from ex3.GameStrategy import GameStrategy


class GameEngine:
    """
    Orchestrates game turns using configurable factory and strategy patterns.
    """

    class Turn:
        """Represents a single game turn with damage tracking."""

        def __init__(
            self,
            cards_played: list[str],
            mana_used: int,
            targets_attacked: list[str],
            damage_dealt: int,
        ) -> None:
            self.cards_played = cards_played
            self.mana_used = mana_used
            self.targets_attacked = targets_attacked
            self.damage_dealt = damage_dealt

    def __init__(self):
        """Initialize game engine with empty state."""
        self.factory: CardFactory | None = None
        self.strategy: GameStrategy | None = None
        self.available_mana: int | None = None
        self.battlefield: list[Card] = []
        self.hand: list[Card] = []
        self.turn: list[GameEngine.Turn] = []
        self.cooldowns = {}

    def configure_engine(self, factory: CardFactory, strategy: GameStrategy):
        """Configure the game engine with a card factory and game strategy."""
        self.factory = factory
        self.strategy = strategy
        self.available_mana = 10

    def simulate_turn(self) -> dict:
        """Simulate a single game turn using the configured strategy."""
        if not all([self.factory, self.strategy, self.available_mana]):
            from ex3.FantasyCardFactory import FantasyCardFactory
            from ex3.AggressiveStrategy import AggressiveStrategy

            self.configure_engine(
                factory=FantasyCardFactory(),
                strategy=AggressiveStrategy(),
            )

        assert self.strategy is not None
        result = self.strategy.execute_turn(
            hand=self.hand,
            battlefield=self.battlefield,
        )
        if result["mana_used"] <= self.available_mana:
            self.available_mana -= result["mana_used"]
            self.turn.append(self.Turn(**result))
        return result

    def get_engine_status(self) -> dict:
        """Return the current game engine status and statistics."""
        return {
            "turns_simulated": len(self.turn),
            "strategy_used": (
                self.strategy.get_strategy_name() if self.strategy else None
            ),
            "total_damage": sum(t.damage_dealt for t in self.turn),
            "cards_created": len(self.hand)
            + len([c for c in self.battlefield if isinstance(c, Card)]),
        }
