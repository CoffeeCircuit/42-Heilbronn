"""
Part 3: The Great Pathway Debate
"""

import alchemy as a
import alchemy.transmutation as t


def ft_pathway_debate() -> None:
    """
    test transmutation and alchemy imports
    """
    print("\n=== Pathway Debate Mastery ===")
    print("\nTesting Absolute Imports (from basic.py):")
    print(f"lead_to_gold(): {t.lead_to_gold()}")
    print(f"stone_to_gem(): {t.stone_to_gem()}")

    print("\nTesting Relative Imports (from advanced.py):")
    print(f"philosophers_stone(): {t.philosophers_stone()}")
    print(f"elixir_of_life(): {t.elixir_of_life()}")

    print("\nTesting Package Access:")
    path = a.transmutation.lead_to_gold()  # type: ignore
    print(f"alchemy.transmutation.lead_to_gold(): {path}")
    path = a.transmutation.philosophers_stone()  # type: ignore
    print(f"alchemy.transmutation.philosophers_stone(): {path}")

    print("\nBoth pathways work! Absolute: clear, Relative: concise")


if __name__ == "__main__":
    ft_pathway_debate()
