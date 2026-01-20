import alchemy.elements as e


def healing_potion() -> str:
    """
    create healing potion using fire and water elements

    :return: Description of the healing potion
    :rtype: str
    """
    msg = f"{e.create_fire()} and {e.create_water()}"
    return "Healing potion brewed with " + msg


def strength_potion() -> str:
    """
    create strength potion using earth and fire elements

    :return: Description of the strength potion
    :rtype: str
    """
    msg = f"{e.create_earth()} and {e.create_fire()}"
    return "Strength potion brewed with " + msg


def invisibility_potion() -> str:
    """
    create invisibility potion using air and water elements

    :return: Description of the invisibility potion
    :rtype: str
    """
    msg = f"{e.create_air()} and {e.create_water()}"
    return "Invisibility potion brewed with " + msg


def wisdom_potion() -> str:
    """
    create wisdom potion using all elements

    :return: Description of the wisdom potion
    :rtype: str
    """
    msg = f"{e.create_air()} and {e.create_water()} and {e.create_fire()} "
    msg += f"{e.create_earth()}"
    return "Wisdom potion brewed with all elements: " + msg
