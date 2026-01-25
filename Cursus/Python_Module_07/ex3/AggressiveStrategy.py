from ex0.Card import Card
from ex0.CreatureCard import CreatureCard
from ex3.FantasyCardFactory import FantasyCardFactory
from ex3.GameStrategy import GameStrategy


class AggressiveStrategy(GameStrategy):
    """
    Strategy that prioritizes dealing maximum damage by attacking with
    highest attack creatures.
    """

    def execute_turn(
        self,
        hand: list[Card],
        battlefield: list[Card],
    ) -> dict:
        """
        Execute an aggressive turn by playing and attacking with the
        strongest creature.
        """

        turn: dict[str, list[str] | int] = {
            "cards_played": [],
            "mana_used": 0,
            "targets_attacked": [],
            "damage_dealt": 0,
        }
        if not hand:
            creature = FantasyCardFactory().create_creature()
            hand.append(creature)
            assert isinstance(turn["mana_used"], int)
            turn["mana_used"] += creature.cost
            return turn

        # Prioritize attacking the weakest target or the player directly
        target = self.prioritize_targets(battlefield).pop()

        creatures = sorted(
            (card for card in hand if isinstance(card, CreatureCard)),
            key=lambda c: c.attack,
            reverse=True,  # playing highest attack first
        )

        creature = creatures.pop()

        assert isinstance(turn["cards_played"], list)
        turn["cards_played"].append(creature.name)

        assert isinstance(turn["mana_used"], int)
        turn["mana_used"] += creature.cost

        assert isinstance(target, CreatureCard)
        attack_result = creature.attack_target(target)

        assert isinstance(turn["targets_attacked"], list)
        turn["targets_attacked"].append(target.name)

        assert isinstance(turn["damage_dealt"], int)
        turn["damage_dealt"] += attack_result["damage_dealt"]

        if target.health <= 0:
            battlefield.remove(target)

        return turn

    def get_strategy_name(self) -> str:
        """Return the name of this strategy."""
        return "Aggressive Strategy"

    def prioritize_targets(self, available_targets: list[Card]) -> list[Card]:
        """Sort targets by lowest health to eliminate weak enemies first."""

        sorted_targets = sorted(
            available_targets,
            key=lambda t: t.health if isinstance(t, CreatureCard) else 0,
        )
        return sorted_targets
