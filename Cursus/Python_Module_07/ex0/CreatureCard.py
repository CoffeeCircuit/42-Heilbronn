from ex0.Card import Card


class CreatureCard(Card):

    def __init__(
        self,
        name: str,
        cost: int,
        rarity: Card.RarityType,
        attack: int,
        health: int,
    ) -> None:
        super().__init__(name, cost, rarity)
        self.type: str = "Creature"
        self.attack = attack
        self.health = health

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
            "effect": "Creature summoned to battlefield",
        }

    def attack_target(self, target: "CreatureCard") -> dict:
        target.health -= min(self.attack, target.health)
        return {
            "attacker": self.name,
            "target": target.name,
            "damage_dealt": self.attack,
            "combat_resolved": target.health <= 0,
        }
