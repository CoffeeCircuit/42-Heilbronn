#!/usr/bin/env python3
"""
Exercise 3: Achievement Hunter
Set manipulation
Authorized: set(), len(), print(), union(), intersection(), difference()
"""


def ft_achievement_tracker():
    """Function will operate on sets"""
    print("=== Achievement Tracker System ===")
    players: dict[str, set] = {
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

    print()
    for name in players:
        achievements = players[name]
        print(f"Player {name} achivements: ", achievements)

    print()
    print("=== Achievement Analytics ===")
    all_achvmnts = {achvmnts for name in players for achvmnts in players[name]}
    print("All unique achievements: ", all_achvmnts)
    print("Total unique achievements: ", len(all_achvmnts))

    print()
    common_set = players["Alice"].intersection(players["Bob"])
    common_set = common_set.intersection(players["Charlie"])
    print("Common to all players: ", common_set)

    rare = players["Alice"].union(players["Bob"])
    rare = rare.union(players["Charlie"])
    print("Rare", rare)

    print()
    alice_bob_common = players["Alice"].intersection(players["Bob"])
    print("Alice vs Bob commmon: ", alice_bob_common)
    print("Alice unique: ", players["Alice"].difference(players["Bob"]))
    print("Bob unique: ", players["Bob"].difference(players["Alice"]))


if __name__ == "__main__":
    ft_achievement_tracker()


""""
• Track unique achievements (no "First Kill" counted twice!)
• Find achievements shared by multiple players (the "common ground")
• Spot the ultra-rare achievements (bragging rights material!)
• See who’s missing what achievements (gotta catch ’em all!)
• Build player communities based on shared accomplishments
"""
