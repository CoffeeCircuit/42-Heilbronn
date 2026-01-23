from ex0.Card import Card


class ArtifactCard(Card):
    def __init__(
        self,
        name: str,
        cost: int,
        rarity: Card.RarityType,
        durability: int,
        effect: str,
    ):
        super().__init__(name, cost, rarity)
        self.durability = durability
        self.effect = effect

    def play(self, game_state: dict) -> dict:
        try:
            if self.is_playable(game_state["available_mana"]):
                game_state["available_mana"] -= self.cost
                game_state["battlefield"].append(self)
                game_state["cooldowns"][self.name] = self.durability
        except KeyError:
            print("Warning: Missing keys in game_state")
        return {
            "card_played": self.name,
            "mana_used": self.cost,
            "effect": "Casting spell",
        }

    def activate_ability(self) -> dict:
        pass
