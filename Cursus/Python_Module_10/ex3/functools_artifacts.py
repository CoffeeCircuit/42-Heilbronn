"""
Exercise 3: Ancient Library
Directory: ex3/
Files to Submit: functools_artifacts.py
Authorized: functools, operator, print()
"""

from collections.abc import Callable
from functools import reduce, partial, lru_cache, singledispatch
from operator import add, mul, ge, lt


def spell_reducer(spells: list[int], operation: str) -> int:
    ops = {
        "sum": add,
        "product": mul,
        "max": lambda a, b: a if ge(a, b) else b,
        "min": lambda a, b: a if lt(a, b) else b,
    }
    if operation not in ops:
        raise KeyError(f"Unsupported operation: {operation}")
    return reduce(ops[operation], spells)


def partial_enchanter(base_enchantment: Callable) -> dict[str, Callable]:
    return {
        "fire_enchant": partial(base_enchantment, power=50, element="Fire"),
        "ice_enchant": partial(base_enchantment, power=50, element="Ice"),
        "lightning_enchant": partial(
            base_enchantment,
            power=50,
            element="Lightning",
        ),
    }


@lru_cache(maxsize=None)
def memoized_fibonacci(n: int) -> int:
    if n < 2:
        return n
    else:
        return memoized_fibonacci(n - 1) + memoized_fibonacci(n - 2)


@singledispatch
def spell_dispatcher(spell) -> Callable:
    return lambda: None


@spell_dispatcher.register
def _(spell: str) -> Callable:
    return lambda: f"Casting enchantment: {spell}"


@spell_dispatcher.register
def _(spell: int) -> Callable:
    return lambda: f"Doing {spell} damage"


@spell_dispatcher.register
def _(spell: list) -> Callable:
    return lambda: f"Multi-cast: {', '.join([f'Casting {s}' for s in spell])}"


def functools_artifacts() -> None:
    """
    main function to demonstrate the functionalities.
    """

    print("\nTesting spell reducer...")
    spells = [10, 20, 5, 15]
    try:
        print("Sum:", spell_reducer(spells, "sum"))
        print("Product:", spell_reducer(spells, "product"))
        print("Max:", spell_reducer(spells, "max"))
        print("Min:", spell_reducer(spells, "min"))
    except KeyError as e:
        print(e)

    print("\nTesting partial enchanter...")

    def enchat(power: int, element: str, target: str) -> str:
        return f"{element} Enchantment of power {power} on {target}"

    enchanters = partial_enchanter(enchat)
    print(enchanters["fire_enchant"](target="Sword"))
    print(enchanters["ice_enchant"](target="Sword"))
    print(enchanters["lightning_enchant"](target="Sword"))

    print("\nTesting memoized fibonacci...")
    fib_numbers = [10, 9, 19]
    for n in fib_numbers:
        print(f"Fib({n}):", memoized_fibonacci(n))

    print("\nTesting spell dispatcher...")
    spell_variants = [
        "Fireball",
        100,
        ["Ice Shard", "Wind Gust", "Earthquake"],
    ]
    for spell in spell_variants:
        action = spell_dispatcher(spell)
        print(action())


if __name__ == "__main__":
    functools_artifacts()
