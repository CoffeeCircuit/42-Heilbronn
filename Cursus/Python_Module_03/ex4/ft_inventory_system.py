#!/usr/bin/env python3
"""
ft_inventory_system
Directory: ex4/
Files to Submit: ft_inventory_system.py
Authorized: dict(), len(), print(), keys(), values(), items(), get(), update()
"""


def ft_inventory_system():
    """
    inventory maneger
    """
    inv = {
        "potion": 5,
        "armor": 3,
        "shield": 2,
        "sword": 1,
        "helmet": 1,
    }

    total = 0
    for v in inv.values():
        total += v

    print("=== Inventory System Analysis ===")
    print(f"Total items in inventory: {total}")
    print(f"Unique item types: {len({v for v in inv.keys()})}\n")

    print("=== Current Inventory ===")
    max_units = 0
    min_units = 1
    for k, v in inv.items():
        print(f"{k}: {v} units ({v/total:.2%})")
        if v > max_units:
            max_units = v
        if v < min_units:
            min_units = v

    print("\n=== Inventory Statistics ===")
    print(f"Most abundant: potion ({max_units} units)")
    print(f"Least abundant: sword ({min_units} unit)")

    print("\n=== Item Categories ===")
    print("Moderate: ", {k: v for k, v in inv.items() if v / total >= 0.3})
    print("Scarce: ", {k: v for k, v in inv.items() if v / total < 0.3})

    print("\n=== Management Suggestions ===")
    print(f"Restock needed: {[k for k ,v in inv.items() if v ==1]}")

    print("\n=== Dictionary Properties Demo ===")
    print("Dictionary keys: ", [k for k in inv.keys()])
    print("Dictionary values: ", [v for v in inv.values()])
    print(f"Sample lookup - 'sword' in inventory: {'sword' in inv.keys()}")


if __name__ == "__main__":
    ft_inventory_system()
