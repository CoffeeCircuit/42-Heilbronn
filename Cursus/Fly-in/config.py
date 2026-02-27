from dataclasses import dataclass
from colors import Color


@dataclass
class Configure:
    width: int = 1024
    height: int = 768
    margin: int = 20
    animation_delay: int = 25
    animation_steps: int = 30
    animation_loop: bool = False
    background: str = "#1e1e2e"
    foreground: str = "#cdd6f4"
    background_image: str = "42.png"
    font = ('System', 11)
    fill_color: str = Color.YELLOW.hex
    text_color: str = Color.RED.hex
    font_weight: str = "normal"
    border_color: str = Color.RED.hex
    border_width: int = 2
    border_radius: int = 20
    edge_text_color: str = ""
    edge_color: str = Color.RED.hex
    edge_width: int = 1
    drone_size: int = 8
    drone_color: str = "red"
    drone_shape: str = "circle"
    drone_outline_color: str = ""
