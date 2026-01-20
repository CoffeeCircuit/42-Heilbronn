"""
Part 4: Breaking the Circular Curse
"""

from alchemy.grimoire import validate_ingredients, record_spell


def ft_circular_curse() -> None:
    """
    test circural dependencies imports
    """
    print("\n=== Circular Curse Breaking ===")

    print("\nTesting ingredient validation:")
    out = validate_ingredients("fire air")
    print(f'validate_ingredients("fire air"): fire air - {out}')
    out = validate_ingredients("dragon scales")
    print(f'validate_ingredients("dragon scales"): dragon scales - {out}')

    print("\nTesting spell recording with validation:")
    out = record_spell("Fireball", "fire air")
    print(f'record_spell("Fireball", "fire air"): {out}')
    out = record_spell("Dark Magic", "shadow")
    print(f'record_spell("Dark Magic", "shadow"): {out}')

    print("\nTesting late import technique:")
    out = record_spell("Lightning", "air")
    print(f'record_spell("Lightning", "air"): {out}')

    print("\nCircular dependency curse avoided using late imports!")
    print("All spells processed safely!")


if __name__ == "__main__":
    ft_circular_curse()
