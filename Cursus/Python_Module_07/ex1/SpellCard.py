from ex0.Card import Card
from enum import StrEnum


class SpellCard(Card):
    class EffectType(StrEnum):
        DAMAGE = "Deal 3 damage to target"
        HEAL = "Heal target by 3"
        BUFF = "Increase target's attack by 3"
        DEBUFF = "Decrease target's attack by 3"

    def __init__(
        self,
        name: str,
        cost: int,
        rarity: Card.RarityType,
        effect_type: EffectType,
    ) -> None:
        super().__init__(name, cost, rarity)
        self.effect_type = effect_type

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
            "effect": self.effect_type.value,
        }

    def resolve_effect(self, targets: list[Card]) -> dict:
        from ex0.CreatureCard import CreatureCard

        for trgt in targets:
            match self.effect_type:
                case self.EffectType.DAMAGE if isinstance(trgt, CreatureCard):
                    trgt.health -= 3
                    return {f"{trgt.name}": self.EffectType.DAMAGE.value}
                case self.EffectType.HEAL if isinstance(trgt, CreatureCard):
                    trgt.health += 3
                    return {f"{trgt.name}": self.EffectType.HEAL.value}
                case self.EffectType.BUFF if isinstance(trgt, CreatureCard):
                    trgt.attack += 3
                    return {f"{trgt.name}": self.EffectType.BUFF.value}
                case self.EffectType.DEBUFF if isinstance(trgt, CreatureCard):
                    trgt.attack -= 3
                    return {f"{trgt.name}": self.EffectType.DEBUFF.value}
        return {}
