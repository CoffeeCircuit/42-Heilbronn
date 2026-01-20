"""
Part 1: Sacred Scroll
"""

import alchemy as alc


def ft_sacred_scroll() -> None:
    """
    test for alchemy/__init__.py
    """
    print("\n=== Sacred Scroll Mastery ===\n")
    print("Testing direct module access:")
    print(f"alchemy.elements.create_fire(): {alc.elements.create_fire()}")
    print(f"alchemy.elements.create_water(): {alc.elements.create_water()}")
    print(f"alchemy.elements.create_earth(): {alc.elements.create_earth()}")
    print(f"alchemy.elements.create_air(): {alc.elements.create_air()}")

    print("\nTesting package-level access (controlled by __init__.py):")
    print(f"alchemy.create_fire(): {alc.create_fire()}")
    print(f"alchemy.create_water(): {alc.create_water()}")

    try:
        print(f"alchemy.create_earth(): {alc.create_earth()}")  # type: ignore
        print(f"alchemy.create_air(): {alc.create_air()}")  # type: ignore
    except AttributeError:
        print("alchemy.create_earth(): AttributeError - not exposed")
        print("alchemy.create_air(): AttributeError - not exposed")

    print("\nPackage metadata:")
    print("Version: ", alc.__version__)
    print("Author: ", alc.__author__)


if __name__ == "__main__":
    ft_sacred_scroll()
