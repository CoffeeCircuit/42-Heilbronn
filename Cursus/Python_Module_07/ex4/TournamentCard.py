from ex0.Card import Card
from ex2.Combatable import Combatable
from ex4.Rankable import Rankable


class TournamentCard(Card, Combatable, Rankable):
    def __init__(
        self,
        name: str,
        cost: int,
        rarity: Card.RarityType,
        attack_power: int,
        rank: int,
    ):
        super().__init__(name, cost, rarity)
        self.attack_power = attack_power
        self.rank = rank

    def play(self, game_state: dict) -> dict:
        try:
            if self.is_playable(game_state["available_mana"]):
                game_state["available_mana"] -= self.cost
                game_state["battlefield"].append(self)
        except KeyError:
            print("Warning: Missing keys in game_state")
        return {
            "card_played": self.name,
            "mana_used": self.cost,
            "effect": "Tournament Card played with combat abilities",
        }

    def get_combat_stats(self) -> dict:
        return {
            "attack_power": self.attack_power,
        }

    def get_rank(self) -> int:
        return self.rank
