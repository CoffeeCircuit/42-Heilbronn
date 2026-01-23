# GameEngine.py - Game orchestrator:
# • Method: configure_engine(factory, strategy)
# • Method: simulate_turn()
# • Method: get_engine_status(

class GameEngine:
    def __init__(self):
        self.factory = None
        self.strategy = None
        self.game_report = {
            "turns_simulated": 0,
            "strategy_used": "",
            "total_damage": 0,
            "cards_created": 0,
        }

    def configure_engine(self, factory, strategy):
        pass

    def simulate_turn(self):
        pass

    def get_engine_status(self):
        pass
