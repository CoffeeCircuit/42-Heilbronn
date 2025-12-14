#!/usr/bin/env python3
"""
Exercise 4: Inventory Master
Dictionary operations
Authorized: dict(), len(), print(), keys(), values(), items(), get(),
update()
"""


def print_inventory(player: str, db: dict[str, dict[str, dict]]):
    print(f"=== {player}'s Inventory ===")
    inventory = db[player]
    inventory_value = 0
    item_count = 0
    categories = dict()
    for item, stats in inventory.items():
        t_val = stats["qty"] * stats["value"]
        inventory_value += t_val
        item_count += stats["qty"]
        if stats["type"] in categories.keys():
            categories[stats["type"]] += stats.get("qty")
        else:
            categories.update({stats["type"]: stats.get("qty")})
        print(f"{item} ({stats['type']}, {stats['rarity']}): ", end="")
        print(f"{stats['qty']}x @ {stats['value']} gold each ", end="")
        print(f"= {t_val} gold")

    print()
    print(f"Inventory value: {inventory_value} gold")
    print(f"Item count: {item_count} items")
    print("Categories: ", end="")
    for cat, count in categories.items():
        print(f"{cat}({count})", end=", ")
    print()


def add_player(player: str, db: dict):
    if player in db.keys():
        raise Exception("Existing player")
    db[player] = dict()


def add_item(player: str, db: dict, item: str, stat: dict[str, int | str]):
    if player not in db.keys():
        raise Exception("Player not found")
    db[player].update({item: stat})


def set_stat(qty: int, val: int, type: str, rare: str) -> dict[str, int | str]:
    return {
        "qty": qty,
        "value": val,
        "type": type,
        "rarity": rare,
    }


def ft_inventory_system():
    """Main function"""
    print("=== Player Inventory System ===")
    print()
    db = dict()

    try:
        add_player("Alice", db)
        add_player("Bob", db)
        add_item("Alice", db, "sword", set_stat(1, 500, "weapon", "rare"))
        add_item(
            "Alice",
            db,
            "potion",
            set_stat(5, 50, "consumable", "common"),
        )
        add_item("Alice", db, "shield", set_stat(1, 200, "armor", "uncommon"))
    except Exception as e:
        print("Error:", e)

    print_inventory("Alice", db)


if __name__ == "__main__":
    ft_inventory_system()
