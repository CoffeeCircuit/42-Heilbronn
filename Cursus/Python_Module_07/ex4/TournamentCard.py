from ex0.Card import Card
from ex0.CreatureCard import CreatureCard
from ex2.Combatable import Combatable
from ex4.Rankable import Rankable


class TournamentCard(Card, Combatable, Rankable):
    def __init__(
        self,
        name: str,
        cost: int,
        rarity: Card.RarityType,
        id: str,
        rating: int,
        power: int,
        health: int,
    ) -> None:
        super().__init__(name, cost, rarity)
        self.id = id
        self.rating = rating
        self.power = power
        self.health = health
        self.wins: int = 0
        self.losses: int = 0
        self.combat_stats: dict

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
            "effect": "Tournament creature summoned",
        }

    def attack(self, target: CreatureCard) -> dict:
        target.health -= min(self.power, target.health)
        self.combat_stats["attacks"] += 1
        return {
            "attacker": self.name,
            "target": target.name,
            "damage_dealt": self.power,
            "combat_resolved": target.health <= 0,
        }

    def defend(self, incoming_damage: int) -> dict:
        damage_taken = min(incoming_damage, self.health)
        self.health -= damage_taken
        self.combat_stats["defenses"] += 1
        return {
            "defender": self.name,
            "damage_taken": damage_taken,
            "survived": self.health >= 0,
        }

    def update_wins(self, wins: int) -> None:
        self.wins += wins

    def update_losses(self, losses: int) -> None:
        self.losses += losses

    def calculate_rating(self) -> int:
        total_matches = self.wins + self.losses
        if total_matches == 0:
            return self.rating
        win_rate = self.wins / total_matches
        self.rating = int(self.rating * (1 + win_rate))
        return self.rating

    def get_combat_stats(self) -> dict:
        return self.combat_stats

    def get_rank_info(self) -> dict:
        return {
            "wins": self.wins,
            "losses": self.losses,
            "rating": self.rating,
        }
