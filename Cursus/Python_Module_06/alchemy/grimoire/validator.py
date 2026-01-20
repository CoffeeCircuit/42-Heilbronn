def validate_ingredients(ingredients: str) -> str:
    """
    validate ingredients for spell casting

    :param ingredients: Ingredients to validate
    :type ingredients: str
    :return: Validation result
    :rtype: str
    """
    valid_ingrediants = {"fire", "water", "earth", "air"}
    for ingredient in ingredients.split():
        if ingredient not in valid_ingrediants:
            return "INVALID"
    return "VALID"
