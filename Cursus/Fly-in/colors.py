from sys import stdout
from enum import Enum


class Color(Enum):
    # Format: (ansi_code, hex_color)
    # Using 256-color palette for consistency
    RESET = (0, "#000000")
    BLACK = (16, "#000000")
    RED = (196, "#FF0000")
    GREEN = (46, "#00FF00")
    YELLOW = (226, "#FFFF00")
    BLUE = (21, "#0000FF")
    PURPLE = (93, "#800080")
    CYAN = (51, "#00FFFF")
    WHITE = (231, "#FFFFFF")
    DEFAULT = (231, "#FFFFFF")
    MAROON = (52, "#800000")
    INDIGO = (54, "#4B0082")
    DARKRED = (88, "#8B0000")
    VIOLET = (93, "#8B00FF")
    BROWN = (94, "#8B4513")
    CRIMSON = (160, "#DC143C")
    ORANGE = (208, "#FFA500")
    GOLD = (214, "#FFD700")
    RAINBOW = (1000, "#FF0000")  # Special case
    LIME = (1000, "#FF0000")  # TODO
    MAGENTA = (1000, "#FF0000")  # TODO

    @property
    def ansi(self) -> int:
        """Get ANSI color code for console output"""
        return self.value[0]

    @property
    def hex(self) -> str:
        """Get hex color code for Tkinter"""
        return self.value[1]


class ColorStr(str):
    def __new__(
        cls,
        text: str,
        fg: Color = Color.DEFAULT,
        bg: Color = Color.DEFAULT,
        bold: bool = False,
    ):
        obj = super().__new__(cls, text)
        obj.fg = fg
        obj.bg = bg
        obj.bold = bold
        return obj

    def __init__(
        self,
        text: str,
        fg: Color = Color.DEFAULT,
        bg: Color = Color.DEFAULT,
        bold: bool = False,
    ):
        pass

    # ...existing code...
    def set_color(
        self,
        fg: str,
        /,
        bg: str = "DEFAULT",
        bold: bool = False,
    ):
        if not stdout.isatty():
            raise EnvironmentError("Environment does not support ANSI codes")
        try:
            self.fg = Color[fg.upper()]
        except KeyError:
            raise ValueError(
                f"Invalid foreground color: {fg!r}. Valid options: "
                f"{[c.name for c in Color]}"
            )
        try:
            self.bg = Color[bg.upper()]
        except KeyError:
            raise ValueError(
                f"Invalid background color: {bg!r}. Valid options: "
                f"{[c.name for c in Color]}"
            )
        self.bold = bold

    def __str__(self) -> str:
        # All colors now use 256-color format for consistency
        if self.fg.ansi == 0:
            fg = "39"
        elif self.fg == Color.DEFAULT:
            fg = "39"
        else:
            fg = f"38;5;{self.fg.ansi}"

        # Handle background color
        if self.bg.ansi == 0:
            bg = "49"
        elif self.bg.ansi == 1000:
            bg = "49"
        elif self.bg == Color.DEFAULT:
            bg = "49"
        else:
            bg = f"48;5;{self.bg.ansi}"

        if self.fg == Color.RAINBOW:
            # Rainbow colors: red, orange, yellow, green, blue, indigo, violet
            r_fg = ("196", "208", "226", "46", "21", "54", "93")
            base_str = str.__str__(self)
            return "".join(
                (
                    f"\033[{int(self.bold)};38;5;{r_fg[i % 7]};{bg}m"
                    f"{c}"
                    f"\033[{Color.RESET.ansi}m"
                )
                for i, c in enumerate(base_str)
            )

        # Build escape sequence
        codes = [str(int(self.bold)), fg, bg]
        return (
            f"\033[{';'.join(codes)}m"
            f"{super().__str__()}"
            f"\033[{Color.RESET.ansi}m"
        )

    def _with_same_color(self, value: str):
        return ColorStr(value, self.fg, self.bg, self.bold)

    def __format__(self, format_spec: str) -> str:
        return self._with_same_color(super().__format__(format_spec))

    def upper(self):
        return self._with_same_color(super().upper())

    def lower(self):
        return self._with_same_color(super().lower())

    def capitalize(self):
        return self._with_same_color(super().capitalize())

    def title(self):
        return self._with_same_color(super().title())

    def swapcase(self):
        return self._with_same_color(super().swapcase())

    def replace(self, old, new, count=-1):
        return self._with_same_color(super().replace(old, new, count))


