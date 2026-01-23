from ex2.EliteCard import EliteCard


def main() -> None:
    print("=== DataDeck Ability System ===\n")

    elite_card = EliteCard(
        name="Arcane Warrior",
        cost=7,
        rarity=EliteCard.RarityType.EPIC,
        attack_power=5,
        magic_power=4,
    )

    print("EliteCard capabilities:")
    for base in elite_card.__class__.__bases__:
        methods = [
            func
            for func in dir(base)
            if callable(getattr(base, func)) and not func.startswith("_")
        ]
        print(f"- {base.__name__}: {methods}")

    print("\nPlaying Arcane Warrior (Elite Card):\n")

    # Simulate combat actions
    print("Combat phase:")
    attack_result = elite_card.attack(target="Enemy")
    print("Attack result:", attack_result)

    defend_result = elite_card.defend(incoming_damage=5)
    print("Defense result:", defend_result)

    # Simulate magical actions
    print("\nMagic phase:")
    spell_result = elite_card.cast_spell(
        spell_name="Fireball", targets=["Enemy1", "Enemy2"]
    )
    print("Spell cast:", spell_result)

    mana_result = elite_card.channel_mana(amount=3)
    print("Mana channel:", mana_result)

    print("\nMultiple interface implementation successful!")


if __name__ == "__main__":
    main()
