"""
Exercise 2: Memory Depths
Directory: ex2/
Files to Submit: scope_mysteries.py
Authorized: nonlocal, print()
"""

from collections.abc import Callable


def mage_counter() -> Callable:
    """
    Returns a function that counts the number of times it has been called.
    """
    counter = 0

    def inc() -> int:
        nonlocal counter
        counter += 1
        return counter

    return inc


def spell_accumulator(initial_power: int) -> Callable:
    """
    Returns a function that accumulates spell power starting from an initial
    value.
    """
    total_power = initial_power

    def power(addition: int) -> int:
        nonlocal total_power
        total_power += addition
        return total_power

    return power


def enchantment_factory(enchantment_type: str) -> Callable:
    """
    Returns a function that enchants an item with the given enchantment type.
    """
    return lambda name: f"{enchantment_type} {name}"


def memory_vault() -> dict[str, Callable]:
    """
    Returns a dictionary with 'store' and 'recall' functions to manage a
    memory vault.
    """
    memory: dict[str, int] = dict()

    def store(key: str, value: int) -> None:
        print(f'Storing "{key}": {value}')
        memory[key] = value

    def recall(key: str) -> str | int:
        return "Memory not found" if key not in memory else memory[key]

    return {
        "store": store,
        "recall": recall,
    }


def scope_mysteries() -> None:
    """Main function to demonstrate scope mysteries."""
    initial_powers = [65, 62, 77]
    power_additions = [8, 9, 16, 14, 18]
    enchantment_types = ["Flaming", "Dark", "Frozen"]
    items_to_enchant = ["Sword", "Shield", "Amulet", "Armor"]

    print("Testing mage counter...")
    counter = mage_counter()
    for _ in range(5):
        print("Call:", counter())

    print("\nTesting spell accumulator...")
    for init_power in initial_powers:
        accumulator = spell_accumulator(init_power)
        for addition in power_additions:
            print(
                f"Adding {addition} to initial power {init_power}: Total:",
                accumulator(addition),
            )

    print("\nTesting enchantment factory...")
    for enchant_type in enchantment_types:
        enchant = enchantment_factory(enchant_type)
        for item in items_to_enchant:
            print(enchant(item))

    print("\nTesting memory vault...")
    mem = memory_vault()
    store = mem["store"]
    recall = mem["recall"]
    store("gold", 150)
    store("silver", 300)
    print("Recalling 'gold':", recall("gold"))
    print("Recalling 'silver':", recall("silver"))
    print("Recalling 'bronze':", recall("bronze"))


if __name__ == "__main__":
    scope_mysteries()
