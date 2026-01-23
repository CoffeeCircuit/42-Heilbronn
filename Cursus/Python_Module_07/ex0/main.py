from ex0 import CreatureCard


def main() -> None:

    print("\n=== DataDeck Card Foundation ===")
    print("\nTesting Abstract Base Class Design:")

    game_state = {
        "available_mana": 12,
        "battlefield": [],
        "cooldowns": {},
    }

    creature = CreatureCard(
        name="Fire Dragon",
        cost=5,
        rarity=CreatureCard.RarityType.LEGENDARY,
        attack=7,
        health=5,
    )

    target_creature = CreatureCard(
        name="Goblin Warrior",
        cost=2,
        rarity=CreatureCard.RarityType.COMMON,
        attack=3,
        health=6,
    )

    print("\nCreatureCard Info:")
    print(creature.get_card_info())
    print(
        f"\nPlaying {creature.name} with",
        f"{game_state['available_mana']} mana available:",
    )

    print(f"Playable: {creature.is_playable(game_state['available_mana'])}")
    print("Play result:", creature.play(game_state))

    target_creature.play(game_state)

    print(f"\n{creature.name} attacks {target_creature.name}:")
    print("Attack result:", creature.attack_target(target_creature))

    print("\nTesting insufficient mana (3 available):")
    print(f"Playable: {creature.is_playable(3)}")

    print("\nAbstract pattern successfully demonstrated!")


if __name__ == "__main__":
    main()
