def record_spell(spell_name: str, ingredients: str) -> str:
    """
    spell recording with late import to avoid circular dependency

    :param spell_name: Name of the spell to record
    :type spell_name: str
    :param ingredients: Ingredients used in the spell
    :type ingredients: str
    :return: Confirmation message of the recorded spell
    :rtype: str
    """
    from .validator import validate_ingredients

    validation = validate_ingredients(ingredients)
    return f"Spell recorded: {spell_name} ({ingredients} - {validation})"
