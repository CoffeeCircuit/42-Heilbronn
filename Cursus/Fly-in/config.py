from dataclasses import dataclass
from colors import Color


@dataclass
class Configure:
    width: int = 1920
    height: int = 1080
    margin: int = 20
    animation_delay: int = 50
    animation_steps: int = 20
    animation_loop: bool = False
    background: str = "#1e1e2e"
    foreground: str = "#cdd6f4"
    font = ("System", 11)
    fill_color: str = Color.YELLOW.hex
    text_color: str = Color.RED.hex
    text_padding: float = 1.2
    font_weight: str = "normal"
    border_color: str = Color.RED.hex
    border_width: int = 2
    border_radius: int = 20
    edge_text_color: str = ""
    edge_color: str = '#89b4fa'
    edge_width: int = 1
    drone_size: int = 8
    drone_color: str = "red"
    drone_shape: str = "circle"
    drone_outline_color: str = ""
