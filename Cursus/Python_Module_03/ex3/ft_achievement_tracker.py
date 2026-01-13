#!/usr/bin/env python3
"""
Exercise 3: Achievement Hunter
Set manipulation
Authorized: set(), len(), print(), union(), intersection(), difference()
"""


def ft_achievement_tracker():
    """Function will operate on sets"""
    print("=== Achievement Tracker System ===")
    players: dict[str, set[str]] = {
        "Alice": {
            "first_kill",
            "level_10",
            "treasure_hunter",
            "speed_demon",
        },
        "Bob": {
            "first_kill",
            "level_10",
            "boss_slayer",
            "collector",
        },
        "Charlie": {
            "level_10",
            "treasure_hunter",
            "boss_slayer",
            "speed_demon",
            "perfectionist",
        },
    }

    alice = players["Alice"]
    bob = players["Bob"]
    charlie = players["Charlie"]

    print()
    for name in players:
        achievements = players[name]
        print(f"Player {name} achievements: ", achievements)

    print()
    print("=== Achievement Analytics ===")
    all_achvmnts = {a for s in players.values() for a in s}
    print("All unique achievements: ", all_achvmnts)
    print("Total unique achievements: ", len(all_achvmnts))

    print()
    common_set = alice.intersection(bob, charlie)
    print("Common to all players: ", common_set)

    rare = {
        x for x in all_achvmnts
        if (x in alice) + (x in bob) + (x in charlie) == 1
    }

    print("Rare achievements (1 player): ", rare)

    print()
    alice_bob_common = alice.intersection(bob)
    print("Alice vs Bob common: ", alice_bob_common)
    print("Alice unique: ", alice.difference(bob))
    print("Bob unique: ", bob.difference(alice))


if __name__ == "__main__":
    ft_achievement_tracker()
