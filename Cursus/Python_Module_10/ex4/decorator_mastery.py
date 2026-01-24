"""
Exercise 4: Master's Tower
Directory: ex4/
Files to Submit: decorator_mastery.py
Authorized: functools.wraps, staticmethod, print()
"""

from collections.abc import Callable
from time import sleep, perf_counter
from functools import wraps


def spell_timer(func: Callable) -> Callable:
    """
    Decorator that measures and prints the execution time of a spell function.
    """

    @wraps(func)
    def wrapper(*args, **kwargs):
        print(f"Casting {func.__name__}...")
        start = perf_counter()
        result = func(*args, **kwargs)
        end = perf_counter()
        duration = end - start  # Convert to milliseconds
        print(f"Spell completed in {duration:.6f} seconds.")
        print(f"Result: {result}")

    return wrapper


def power_validator(min_power: int) -> Callable:
    """
    Decorator that validates if the power level meets the minimum required
    power.
    """

    def decorator(func: Callable) -> Callable:
        @wraps(func)
        def wrapper(*args, power: int, **kwargs):
            if power < min_power:
                print("Insufficient power for this spell")
                return None
            return func(*args, power=power, **kwargs)

        return wrapper

    return decorator


def retry_spell(max_attempts: int) -> Callable:
    """
    Decorator that retries a spell function up to max_attempts times if it
    raises an exception.
    """

    def decorator(func: Callable) -> Callable:
        @wraps(func)
        def wrapper(*args, **kwargs):
            attempts = 0
            while attempts < max_attempts:
                try:
                    return func(*args, **kwargs)
                except Exception:
                    attempts += 1
                    print(
                        "Spell failed, retrying...",
                        f"(attempt {attempts}/{max_attempts})",
                    )
            print("Spell casting failed after max_attempts attempts")
            return None

        return wrapper

    return decorator


class MageGuild:
    def __init__(self, name: str, /, *names: str) -> None:
        self.names = (name,) + names

    @staticmethod
    def validate_mage_name(names: list[str]) -> bool:
        """
        Validate mage names to ensure they are at least 3 characters long
        and contain only letters and spaces.
        """
        from string import ascii_letters

        return all(
            map(
                lambda name: len(name) >= 3
                and all(c in ascii_letters + " " for c in name),
                names,
            )
        )

    @power_validator(min_power=10)
    def cast_spell(self, spell_name: str, power: int) -> str:
        """
        Cast a spell with the given name and power.
        """
        return f"Successfully cast {spell_name} with power {power}"


def decorator_mastery() -> None:
    """
    main function to test decorator_mastery module.
    """
    test_powers = [5, 18, 11, 20]
    spell_names = ["tornado", "heal", "meteor", "darkness"]
    mage_names = ["Ember", "Luna", "Nova", "Alex", "Storm", "Riley"]
    invalid_names = ["Jo", "A", "Alex123", "Test@Name"]

    print("\nTesting spell_timer decorator:")

    @spell_timer
    def fireball():
        sleep(0.1)  # Simulate casting time
        return "Fireball spell cast!"

    fireball()

    print("\nTesting power_validator decorator:")

    @power_validator(min_power=10)
    def spell(power: int) -> None:
        print(f"Spell cast with power {power}!")

    for p in test_powers:
        spell(power=p)

    print("\nTesting retry_spell decorator:")

    @retry_spell(max_attempts=3)
    def unstable_spell(spell_name: str) -> str:
        from random import random

        if random() < 0.7:  # 70% chance to fail
            raise Exception("Spell failed!")
        return f"{spell_name} spell cast successfully!"

    for name in spell_names:
        result = unstable_spell(name)
        if result:
            print(result)
            print()

    print("\nTesting MageGuild class:")
    valid = MageGuild.validate_mage_name(mage_names)
    print(f"Test valid mage names: {mage_names} = {valid}")
    invalid = MageGuild.validate_mage_name(invalid_names)
    print(f"Test invalid mage names: {invalid_names} = {invalid}")
    guild = MageGuild(*mage_names)
    for power, spell_name in zip(test_powers, spell_names):
        result = guild.cast_spell(spell_name, power=power)
        if result:
            print(result)


if __name__ == "__main__":
    decorator_mastery()
