from ex0.Card import Card
from ex2.Combatable import Combatable
from ex2.Magical import Magical


class EliteCard(Card, Combatable, Magical):
    def __init__(
        self,
        name: str,
        cost: int,
        rarity: Card.RarityType,
        attack_power: int,
        magic_power: int,
    ):
        super().__init__(name, cost, rarity)
        self.attack_power = attack_power
        self.magic_power = magic_power

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
            "effect": "Combat and Magic abilities activated",
        }

    def attack(self, target) -> dict:
        return {
            "attacker": self.name,
            "target": target,
            "damage": 5,
            "combat_type": "melee",
        }

    def defend(self, incoming_damage: int) -> dict:
        return {
            "defender": self.name,
            "damage_taken": incoming_damage,
            "damage_blocked": 3,
            "still_alive": True if incoming_damage < 10 else False,
        }

    def get_combat_stats(self) -> dict:
        return {
            "attack_power": self.attack_power,
        }

    def cast_spell(self, spell_name: str, targets: list) -> dict:
        return {
            "caster": self.name,
            "spell": spell_name,
            "targets": targets,
            "mana_used": 4,
        }

    def channel_mana(self, amount: int) -> dict:
        return {"channeled": amount, "total_mana": 7}

    def get_magic_stats(self) -> dict:
        return {
            "magic_power": self.magic_power,
        }
