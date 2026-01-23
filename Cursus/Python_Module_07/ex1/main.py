from ex0 import CreatureCard
from ex1 import SpellCard, ArtifactCard
from ex1.Deck import Deck


def main() -> None:
    print("\n=== DataDeck Deck Builder ===")
    print("\nBuilding deck with different card types...")

    game_state = {
        "available_mana": 12,
        "battlefield": [],
        "cooldowns": {},
    }

    deck = Deck()

    deck.add_card(
        SpellCard(
            name="Lightning Bolt",
            cost=3,
            rarity=SpellCard.RarityType.RARE,
            effect_type=SpellCard.EffectType.DAMAGE,
        ),
    )

    deck.add_card(
        ArtifactCard(
            name="Mana Crystal",
            cost=2,
            rarity=ArtifactCard.RarityType.UNCOMMON,
            durability=5,
            effect="Permanent: +1 mana per turn",
        ),
    )

    deck.add_card(
        CreatureCard(
            name="Fire Dragon",
            cost=5,
            rarity=CreatureCard.RarityType.LEGENDARY,
            attack=7,
            health=5,
        ),
    )

    deck.shuffle()
    print("Deck stats:", deck.get_deck_stats())

    print("Drawing and playing cards:")
    while deck.cards:
        card = deck.draw_card()
        if card:
            print(f"\nDrew: {card.name} ({card.__class__.__name__})")

            play_result = card.play(game_state)
            print("Play result:", play_result)
            if isinstance(card, ArtifactCard):
                print(
                    "Artifact effect active for:",
                    game_state["cooldowns"][card.name],
                    "turns",
                )

            if isinstance(card, SpellCard):
                card.resolve_effect(game_state["battlefield"])

    print(
        "\nPolymorphism in action:",
        "Same interface, different card behaviors!",
    )


if __name__ == "__main__":
    main()
