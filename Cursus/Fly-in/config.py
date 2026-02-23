from dataclasses import dataclass


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
    font_type: str = "System"
    font_size: int = 11
    hub_fill_color: str = ""
    hub_text_color: str = ""
    hub_font_weight: str = "normal"
    hub_border_color: str = ""
    hub_border_width: int = 3
    hub_border_radius: tuple[int, int, int, int] = (20, 20, 20, 20)
    edge_text_color: str = ""
    edge_arrow: bool = True
    edge_dash: tuple[int, ...] = ()
    edge_color: str = ""
    edge_width: int = 1
    drone_size: int = 8
    drone_color: str = "red"
    drone_shape: str = "circle"
    drone_outline_color: str = ""
