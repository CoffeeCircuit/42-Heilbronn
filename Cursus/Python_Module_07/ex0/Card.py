from abc import ABC, abstractmethod
from enum import StrEnum


class Card(ABC):

    class RarityType(StrEnum):
        COMMON = "Common"
        UNCOMMON = "Uncommon"
        RARE = "Rare"
        LEGENDARY = "Legendary"
        EPIC = "Epic"

    def __init__(self, name: str, cost: int, rarity: RarityType):
        super().__init__()
        self.name = name
        self.cost = cost
        self.rarity = rarity

    @abstractmethod
    def play(self, game_state: dict) -> dict:
        pass

    def get_card_info(self) -> dict:
        return {k: v for k, v in vars(self).items()}

    def is_playable(self, available_mana: int) -> bool:
        return available_mana >= self.cost
