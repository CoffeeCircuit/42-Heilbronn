from ex4.TournamentCard import TournamentCard


class TournamentPlatform:

    def __init__(self) -> None:
        self.cards: list[TournamentCard] = []
        self.matches = 0

    def register_card(self, card: TournamentCard) -> str:
        self.cards.append(card)
        return f"{card.name} registered!"

    def create_match(self, card1_id: str, card2_id: str) -> dict:
        card1 = next((c for c in self.cards if c.id == card1_id), None)
        card2 = next((c for c in self.cards if c.id == card2_id), None)

        if not card1 or not card2:
            return {"error": "One or both cards not found."}

        self.matches += 1

        if card1.power > card2.power:
            card1.update_wins(1)
            card2.update_losses(1)
            winner = card1
            loser = card2
        elif card2.power > card1.power:
            card2.update_wins(1)
            card1.update_losses(1)
            winner = card2
            loser = card1
        else:
            return {"result": "Draw", "card1": card1.name, "card2": card2.name}

        return {
            "winner": winner.name,
            "loser": loser.name,
            "winner_rating": winner.calculate_rating(),
            "loser_rating": loser.calculate_rating(),
        }

    def get_leaderboard(self) -> list:
        self.cards.sort(reverse=True, key=TournamentCard.calculate_rating)
        return self.cards

    def generate_tournament_report(self) -> dict:
        return {
            "matches_played": self.matches,
            "total_cards": len(self.cards),
            "avg_rating": sum(card.rating for card in self.cards) / len(self.cards),
            "platform_status": "active",
        }
