from .basic import lead_to_gold
from ..potions import healing_potion


def philosophers_stone() -> str:
    """
    create philosopher's stone using lead to gold and healing potion

    :return: Description of the created philosopher's stone
    :rtype: str
    """
    msg = f"{lead_to_gold()} and {healing_potion()}"
    return "Philosopher’s stone created using " + msg


def elixir_of_life() -> str:
    """
    create elixir of life using philosopher's stone

    :return: Description of the created elixir of life
    :rtype: str
    """
    return "Elixir of life: eternal youth achieved!"
