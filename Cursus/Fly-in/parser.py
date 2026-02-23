from pathlib import Path
from colors import ColorStr, Color
from graph import Hub, Graph, Zone


class ParseError(Exception):
    def __init__(
        self,
        msg: str,
        path: Path,
        line: int,
        col: int,
        content: str,
    ) -> None:
        self.msg = msg
        self.path = path
        self.line = line
        self.col = col
        self.content = content

    def __str__(self) -> str:
        mark = "^"
        location = ColorStr(
            f"{self.path.relative_to(Path.cwd())}:{self.line + 1}"
            f":{self.col + 1}",
            fcolor=Color.YELLOW,
            bold=True,
        )
        return (
            f"{location} "
            f"{ColorStr('error: ', fcolor=Color.RED, bold=True)}"
            f"{self.msg}\n"
            f"{self.line + 1:>5} | {self.content.strip()}\n"
            f"{' ' * len(str(self.line)):>5} | "
            f"{ColorStr(f'{mark:>{self.col + 1}}', fcolor=Color.GREEN)}"
        )


class Parser:
    def __init__(self) -> None:
        self.graph: Graph = Graph()

    def parse(self, file: str) -> bool:
        try:
            fp = open(file)
            for i, line in enumerate(fp):
                comment = line.find("#") if line.find("#") != -1 else None
                if (line := line[:comment]).strip() == "":
                    continue
                if ":" not in line:
                    raise ParseError(
                        "Missing ':' separator",
                        Path(file),
                        i,
                        len(line.split(" ", 1)[0]),
                        line,
                    )
                key, val = map(str.strip, line.split(":", 1))
                match key:
                    case "nb_drones":
                        if self.graph.nb_drones != 0:
                            raise ParseError(
                                "Duplicate nb_drones definition",
                                Path(file),
                                i,
                                0,  # TODO modify col to also be a str
                                line,
                            )
                        self.graph.nb_drones = int(
                            val
                        )  # TODO you should double check if val is a valid int
                    case key if key.endswith("hub"):
                        name, x, y, meta_str = val.split(" ", 3)

                        # TODO this is not enough since it can have multiple []
                        if not meta_str.startswith("["):
                            raise (
                                ParseError(
                                    "missing opening '['",
                                    Path(file),
                                    i,
                                    line.find(meta_str),
                                    line,
                                )
                            )
                        if not meta_str.endswith("]"):
                            raise ParseError(
                                "missing closing ']'",
                                Path(file),
                                i,
                                line.find(meta_str) + len(meta_str),
                                line,
                            )

                        meta = {}
                        for arg_ in meta_str.split(" "):
                            k, v = map(str.strip, arg_.strip("[]").split("="))
                            match k:
                                case "color":
                                    meta.update({k: Color[v.upper()].value})
                                case "zone":
                                    meta.update({k: Zone[v.upper()].value})
                                case "max_drones":
                                    meta.update({k: int(v)})
                                case _:
                                    raise KeyError(f"Key {k} not allowed")

                        self.graph.add_hub(Hub(name, int(x), int(y), **meta))

                    case "connection":
                        nodes, *meta = map(str.strip, val.split(" "))
                        n1, n2 = map(str.strip, nodes.split("-"))
                        n1 = next(
                            k for k in self.graph.graph.keys() if k.name == n1
                        )
                        n2 = next(
                            k for k in self.graph.graph.keys() if k.name == n2
                        )
                        if meta:
                            if len(meta) != 1:
                                raise ValueError
                            key, cap = map(
                                lambda x: x.strip("[]"), meta[0].split("=")
                            )
                            if key != "max_link_capacity":
                                raise ValueError
                            self.graph.add_connection(n1, n2, int(cap))
                        else:
                            self.graph.add_connection(n1, n2)

        except Exception as e:
            print(e)
            return False
        return True


parser = Parser()
parser.parse("/home/abalcu/Fly-in/maps/hard/03_ultimate_challenge.txt")

# print(parser.graph)

# TODO
# No Error on Duplicate Connections:
# The code does not check for duplicate connections (e.g., both A-B and B-A).

# No Validation for Unique Zone Names:
# It does not enforce unique hub names.

# No Validation for Required Hubs:
# It does not check for exactly one start_hub and one end_hub.

# No Validation for Zone Name Characters:
# Zone names can contain dashes or spaces, which should be disallowed.

# No Metadata Validation:
# Metadata parsing assumes all key-value pairs are valid and present.

# No Error on Invalid Zone Types:
# Zone type is not checked against allowed values.

# No Capacity Validation:
# Capacity values are not checked to be positive integers.

# No Error Reporting with Line Numbers for All Cases:
# Only some errors report the line number and file.

# No Handling for Connection Metadata:
# The parser ignores any metadata for connections.


print([(k.x, k.y) for k in parser.graph])
