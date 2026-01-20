from alchemy.elements import create_fire, create_earth


def lead_to_gold() -> str:
    """
    create lead to gold transmutation using fire element

    :return: Description of the lead to gold transmutation
    :rtype: str
    """
    return f"Lead transmuted to gold using {create_fire()}"


def stone_to_gem() -> str:
    """
    create stone to gem transmutation using earth element

    :return: Description of the stone to gem transmutation
    :rtype: str
    """
    return f"Stone transmuted to gem using {create_earth()}"
