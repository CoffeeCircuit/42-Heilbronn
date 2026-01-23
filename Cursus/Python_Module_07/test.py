from enum import StrEnum, auto

class SpellEffectType(StrEnum):
    damage = "fobar"
    heal = "heal"
    buff = "buff"
    debuff = "debuff"

print(SpellEffectType("damage"))
