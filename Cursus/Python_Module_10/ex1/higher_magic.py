"""
Exercise 1: Higher Realm
Directory: ex1/
Files to Submit: higher_magic.py
Authorized: callable(), print()
"""

from collections.abc import Callable


def spell_combiner(spell1: Callable, spell2: Callable) -> Callable:
    """
    Combines two spells into one by applying spell1 and then spell2
    to the target.
    """
    return lambda target: (spell1(target), spell2(target))


def power_amplifier(base_spell: Callable, multiplier: int) -> Callable:
    """
    Amplifies the effect of a base spell by a given multiplier.
    """

    def amplify(target):
        return f"{base_spell(target)}, Amplified: {target * multiplier}"

    return amplify


def conditional_caster(condition: Callable, spell: Callable) -> Callable:
    """
    Casts a spell if the condition is callable, otherwise returns a fizzled
    spell.
    """
    if callable(condition):
        return lambda target: f"Speell casted on {target}"
    else:
        return lambda _: "Spell fizzled"


def spell_sequence(spells: list[Callable]) -> Callable:
    """
    Applies a sequence of spells to a target.
    """
    return lambda target: [spell(target) for spell in spells]


def higher_magic():
    """
    Test functions for higher_magic module.
    """
    test_values = [24, 13, 10]
    test_targets = ["Dragon", "Goblin", "Wizard", "Knight"]

    print("Testing spell combiner...")
    for target in test_targets:
        spell_combiner(
            lambda x: f"Fireball hits {x}!",
            lambda x: f"Heals {x}",
        )(target)

    print("\nTesting power amplifier...")
    for val in test_values:
        print(power_amplifier(lambda x: f"Orignal {x}", 3)(val))

    print("\nTesting conditional caster...")
    print("Condition is True:")
    for target in test_targets:
        print(
            conditional_caster(
                lambda x: x == "Dragon",
                lambda x: f"Lightning strikes {x}!",
            )(target)
        )
    print("Condition is False:")
    for target in test_targets:
        print(
            conditional_caster(
                "Not a function",  # type: ignore
                lambda x: f"Lightning strikes {x}!",
            )(target)
        )

    print("\nTesting spell sequence...")
    print("Sequence: Freeeze, Burn, Shock")
    spells = [
        lambda x: f"Freeze {x}",
        lambda x: f"Burn {x}",
        lambda x: f"Shock {x}",
    ]
    print("Applying to Dragon")
    print(spell_sequence(spells)(test_targets[0]))


if __name__ == "__main__":
    higher_magic()
