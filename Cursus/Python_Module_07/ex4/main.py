from ex4.TournamentCard import TournamentCard
from ex4.TournamentPlatform import TournamentPlatform


def main() -> None:

    print("\n=== DataDeck Tournament Platform ===")
    print("\nRegistering Tournament Cards...")

    platform = TournamentPlatform()

    card1 = TournamentCard(
        name="Fire Dragon",
        cost=5,
        rarity=TournamentCard.RarityType.LEGENDARY,
        id="dragon_001",
        rating=1200,
        power=7,
        health=5,
    )

    card2 = TournamentCard(
        name="Ice Wizard",
        cost=4,
        rarity=TournamentCard.RarityType.RARE,
        id="wizard_001",
        rating=1150,
        power=5,
        health=4,
    )

    print(f"\n{card1.name} (ID: {card1.id}):")
    print(f"- Interfaces: {[base.__name__ for base in card1.__class__.__bases__]}")
    print(f"- Rating: {card1.rating}")
    print(f"- Record: {card1.wins}-{card1.losses}")

    print(f"\n{card2.name} (ID: {card2.id}):")
    print(f"- Interfaces: {[base.__name__ for base in card2.__class__.__bases__]}")
    print(f"- Rating: {card2.rating}")
    print(f"- Record: {card2.wins}-{card2.losses}")

    platform.register_card(card1)
    platform.register_card(card2)

    print("\nCreating tournament match...")
    match_result = platform.create_match(card1.id, card2.id)
    print("Match result:", match_result)

    print("\nTournament Leaderboard:")
    leaderboard = platform.get_leaderboard()
    for rank, card in enumerate(leaderboard, start=1):
        print(
            f"{rank}. {card.name} - Rating: {card.rating} ({card.wins}-{card.losses})"
        )

    report = platform.generate_tournament_report()
    print("\nPlatform Report:")
    print(report)

    print(
        "\n=== Tournament Platform Successfully Deployed! ==="
        "\nAll abstract patterns working together harmoniously!"
    )


if __name__ == "__main__":
    main()
