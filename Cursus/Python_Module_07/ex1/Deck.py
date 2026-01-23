from ex0.Card import Card
from random import shuffle


class Deck:
    def __init__(self):
        self.cards: list[Card] = []

    def add_card(self, card: Card) -> None:
        self.cards.append(card)

    def remove_card(self, card_name: str) -> bool:
        try:
            self.cards.remove(
                next(card for card in self.cards if card.name == card_name)
            )
            return True
        except StopIteration:
            return False

    def shuffle(self) -> None:
        shuffle(self.cards)

    def draw_card(self) -> Card | None:
        return self.cards.pop(0) if self.cards else None

    def get_deck_stats(self) -> dict:
        from ex0.CreatureCard import CreatureCard
        from ex1.SpellCard import SpellCard
        from ex1.ArtifactCard import ArtifactCard

        def get_type_count(card_type: type) -> int:
            return len(
                [card for card in self.cards if isinstance(card, card_type)],
            )

        return {
            "total_cards": len(self.cards),
            "creatures": get_type_count(CreatureCard),
            "spells": get_type_count(SpellCard),
            "artifacts": get_type_count(ArtifactCard),
            "avg_cost": round(
                (
                    sum(card.cost for card in self.cards) / len(self.cards)
                    if self.cards
                    else 0
                ),
                2,
            ),
        }
