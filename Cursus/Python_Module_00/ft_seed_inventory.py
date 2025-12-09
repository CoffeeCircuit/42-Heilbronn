def ft_seed_inventory(seed_type: str, quantity: int, unit: str) -> None:
    if unit.lower() == "packets":
        p_units = "packets available"
    elif unit.lower() == "grams":
        p_units = "grams total"
    elif unit.lower() == "area":
        p_units = f"covers {quantity} square meters"
    else:
        p_units = "Unknown unit type"
    print(f"{seed_type.capitalize()} seeds: {quantity} {p_units}")
