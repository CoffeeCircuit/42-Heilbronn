"""
Exercise 0: Lambda Sanctum
Directory: ex0/
Files to Submit: lambda_spells.py
Authorized: map, filter, sorted, print()
"""


def artifact_sorter(artifacts: list[dict]) -> list[dict]:
    """
    Sort artifacts by their power in descending order.

    :param artifacts: List of artifact dictionaries
    :type artifacts: list[dict]
    :return: Sorted list of artifact dictionaries
    :rtype: list[dict[Any, Any]]
    """
    return sorted(artifacts, key=lambda d: d["power"], reverse=True)


def power_filter(mages: list[dict], min_power: int) -> list[dict]:
    """
    Filter mages by minimum power.

    :param mages: List of mage dictionaries
    :type mages: list[dict]
    :param min_power: Minimum power threshold
    :type min_power: int
    :return: Filtered list of mage dictionaries
    :rtype: list[dict[Any, Any]]
    """
    return list(filter(lambda mage: mage["power"] >= min_power, mages))


def spell_transformer(spells: list[str]) -> list[str]:
    """
    Transform spells by adding asterisks around each spell.

    :param spells: List of spell names
    :type spells: list[str]
    :return: Transformed list of spell names
    :rtype: list[str]
    """
    return list(map(lambda x: f"* {x} *", spells))


def mage_stats(mages: list[dict]) -> dict:
    """
    Calculate statistics for mages' power.

    :param mages: List of mage dictionaries
    :type mages: list[dict]
    :return: Dictionary with max, min, and average power
    :rtype: dict
    """
    return {
        "max_power": max(mages, key=lambda d: d["power"])["power"],
        "min_power": min(mages, key=lambda d: d["power"])["power"],
        "avg_power": sum(map(lambda d: d["power"] / len(mages), mages)),
    }


def lambda_spells() -> None:
    """
    Main function to demonstrate the functionality of the module.
    """

    # Sample data generated with data_generator.py
    artifacts = [
        {"name": "Lightning Rod", "power": 111, "type": "focus"},
        {"name": "Water Chalice", "power": 92, "type": "accessory"},
        {"name": "Ice Wand", "power": 106, "type": "focus"},
        {"name": "Lightning Rod", "power": 63, "type": "armor"},
    ]

    mages = [
        {"name": "Casey", "power": 97, "element": "water"},
        {"name": "River", "power": 94, "element": "earth"},
        {"name": "Riley", "power": 55, "element": "fire"},
        {"name": "Ember", "power": 86, "element": "light"},
        {"name": "Jordan", "power": 91, "element": "lightning"},
    ]
    spells = ["blizzard", "freeze", "darkness", "flash"]

    print("\nTesting artifact_sorter...")
    for artifact in artifact_sorter(artifacts):
        print(artifact.get("name"), (artifact.get("power")), "comes before")

    print("\nTesting spell_transformer...")
    for spell in spell_transformer(spells):
        print(spell, end=" ")

    print("\n\nTesting power_filter with min_power=90...")
    for mage in power_filter(mages, 90):
        print(mage.get("name"), "with power", mage.get("power"))

    print("\nTesting mage_stats...")
    stats = mage_stats(mages)
    ms = f"""Most powerful mage’s power level: {stats['max_power']}
Least powerful mage’s power level: {stats['min_power']}
Average power level (rounded to 2 decimals): {stats['avg_power']:.2f}
"""
    print(ms)


if __name__ == "__main__":
    lambda_spells()
