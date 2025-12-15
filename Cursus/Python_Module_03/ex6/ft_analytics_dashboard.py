#!/usr/bin/env python3
"""
Exercise 6: Data Alchemist
Authorized: List/dict/set comprehensions, len(), print(), sum(), max(),
min(), sorted()
"""


def ft_analytics_dashboard():
    "comprehensions examples"
    print("=== Game Analytics Dashboard ===")

    pl = {
        "alice": [2300, True, 5],
        "bob": [1800, True, 3],
        "charlie": [2150, True, 7],
        "diana": [2050, False, 0],
    }

    print()
    print("=== List Comprehension Examples ===")
    print("High scores (>2000):", [k for k, v in pl.items() if v[0] > 2000])
    print("Scores doubled:", [v[0] * 2 for k, v in pl.items()])
    print("Active players:", [k for k, v in pl.items() if v[1] is True])

    print()
    print("=== Dict Comprehension Examples ===")
    print("Player scores:", {k: v[0] for k, v in pl.items()})
    print("")

    print()
    print("=== Set Comprehension Examples ===")
    print("Unique players:", {k for k in pl})

    print()
    print("=== Combined Analysis ===")
    print(f"Total players: {len(pl)}")

    achievements = sum([v[2] for v in pl.values() if v[2] > 3])
    print(f"Total unique achievements: {achievements}")

    print(f"Average score: {sum([v[0] for v in pl.values()])/len(pl)}")

    tp = [k for k, v in pl.items() if v[0] == max([v[0] for v in pl.values()])]
    tpp, tpa = (pl[tp[0]][0], pl[tp[0]][2])
    print(f"Top performer: {tp[0]} ({tpp} points, {tpa} achievements)")


if __name__ == "__main__":
    ft_analytics_dashboard()
