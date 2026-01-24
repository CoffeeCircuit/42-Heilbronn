from ex0.Card import Card
from ex3.CardFactory import CardFactory
from random import choice, randint


class FantasyCardFactory(CardFactory):
    """Factory for creating fantasy-themed game cards."""

    def create_creature(self, name_or_power: str | int | None = None) -> Card:
        """
        Create a fantasy creature card with optional name or attack power.
        """
        from ex0.CreatureCard import CreatureCard

        rand_name = choice(["Dragon", "Goblin", "Elf", "Troll"])

        if isinstance(name_or_power, str):
            name = name_or_power
            attack = randint(1, 10)
        elif isinstance(name_or_power, int):
            name = rand_name
            attack = name_or_power
        else:
            name = rand_name
            attack = randint(1, 10)

        return CreatureCard(
            name=name,
            attack=attack,
            cost=randint(3, 7),
            rarity=choice(list(CreatureCard.RarityType)),
            health=randint(5, 10),
        )

    def create_spell(self, name_or_power: str | int | None = None) -> Card:
        """Create a fantasy spell card with optional name."""
        from ex1.SpellCard import SpellCard

        if isinstance(name_or_power, str):
            name = name_or_power
        else:
            name = choice(["Fireball", "Ice Shard", "Lightning Bolt", "Heal"])

        return SpellCard(
            name=name,
            cost=randint(2, 5),
            rarity=choice(list(SpellCard.RarityType)),
            effect_type=choice(list(SpellCard.EffectType)),
        )

    def create_artifact(self, name_or_power: str | int | None = None) -> Card:
        """Create a fantasy artifact card with optional name or durability."""
        from ex1.ArtifactCard import ArtifactCard

        rand_choice = choice(
            [
                {"name": "Mana Crystal", "efect": "+1 mana per turn"},
                {"name": "Sword of Power", "efect": "+2 attack to equipped"},
                {"name": "Ring of Wisdom", "efect": "Draw an extra cardn"},
                {"name": "Shield of Defense", "efect": "+3 health"},
                {"name": "Crown of Kings", "efect": " +1 cost reduction"},
                {"name": "Boots of Speed", "efect": "+1 mana regeneration"},
                {"name": "Cloak of Shadows", "efect": "Stealth ability"},
                {"name": "Staff of Elements", "efect": "+1 spell damage"},
            ]
        )

        rand_name = rand_choice["name"]
        rand_effect = rand_choice["efect"]

        if isinstance(name_or_power, str):
            name = name_or_power
            durability = randint(3, 8)
        elif isinstance(name_or_power, int):
            durability = name_or_power
            name = rand_name
        else:
            name = rand_name
            durability = randint(3, 8)

        return ArtifactCard(
            name=name,
            cost=randint(1, 4),
            rarity=choice(list(ArtifactCard.RarityType)),
            durability=durability,
            effect=rand_effect,
        )

    def create_themed_deck(self, size: int) -> dict:
        """Create a themed deck with specified number of each card type."""
        deck = {
            "creatures": [],
            "spells": [],
            "artifacts": [],
        }
        for _ in range(size):
            deck["creatures"].append(self.create_creature())
            deck["spells"].append(self.create_spell())
            deck["artifacts"].append(self.create_artifact())
        return deck

    def get_supported_types(self) -> dict:
        """Return all supported fantasy card types."""
        return {
            "creatures": ["dragon", "goblin", "elf", "troll"],
            "spells": ["fireball", "ice shard", "lightning bolt", "heal"],
            "artifacts": [
                "mana_crystal",
                "sword_of_power",
                "ring_of_wisdom",
                "shield_of_defense",
                "crown_of_kings",
                "boots_of_speed",
                "cloak_of_shadows",
                "staff_of_elements",
            ],
        }
