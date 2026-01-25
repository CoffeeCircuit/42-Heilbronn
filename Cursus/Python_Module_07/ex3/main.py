from ex3.GameEngine import GameEngine
from ex3.FantasyCardFactory import FantasyCardFactory
from ex3.AggressiveStrategy import AggressiveStrategy


def main() -> None:
    print("\n=== DataDeck Game Engine ===\n")

    print("Configuring Fantasy Card Game...")
    engine = GameEngine()
    factory = FantasyCardFactory()
    strategy = AggressiveStrategy()
    engine.configure_engine(factory=factory, strategy=strategy)

    print("Factory:", factory.__class__.__name__)
    print("Strategy:", strategy.__class__.__name__)
    print("Available types:", factory.get_supported_types())

    print("\nSimulating aggressive turn...")
    engine.hand = [
        factory.create_creature("Goblin Warrior"),
        factory.create_creature("Orc Warrior"),
        factory.create_spell("Lightning bolt"),
    ]

    engine.battlefield = [factory.create_creature("Elf Archer")]
    print("Hand:", [f"{card.name} ({card.cost})" for card in engine.hand])
    result = engine.simulate_turn()

    print("\nTurn execution:")
    print("Strategy:", strategy.get_strategy_name())
    print("Actions:", result)

    print("\nGame Report:")
    status = engine.get_engine_status()
    print(status)
    print(
        "\nAbstract Factory + Strategy Pattern:",
        "Maximum flexibility achieved!",
    )


if __name__ == "__main__":
    main()
