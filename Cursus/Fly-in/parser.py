from pathlib import Path
from colors import ColorStr, Color
from typing import Optional, TypedDict

StringPath = str | Path


class ErrorInfo(TypedDict):
    msg: str
    file: str
    line: int
    col: int
    content: str


class ParserError(Exception):
    def __init__(
        self,
        *,
        msg: Optional[str] = None,
        file: Optional[str] = None,
        line: Optional[int] = None,
        col: Optional[int] = None,
        content: Optional[str] = None,
    ) -> None:
        self.err_msg: str
        if all(map(lambda f: f is not None, (file, line, col, content))):
            assert file is not None
            assert line is not None
            assert col is not None
            _file = Path(file).resolve().relative_to(Path.cwd())
            _location = f"{_file}:{line + 1}:{col + 1}"
            self.err_msg = (
                f"{ColorStr(f'{_location}', Color.YELLOW, bold=True)} "
                f"{ColorStr('error:', Color.RED, bold=True)} {msg}\n"
                f"{line + 1} | {content}"
                f"{' ' * len(str(line))} | "
                f"{ColorStr('^'.rjust(col + 1), Color.GREEN)}"
            )
        elif file is not None and all(
            map(lambda f: f is None, (line, col, content))
        ):
            _file = Path(file).resolve().relative_to(Path.cwd())
            self.err_msg = (
                f"{ColorStr(f'{_file}', Color.YELLOW, bold=True)} "
                f"{ColorStr('error:', Color.RED, bold=True)} {msg}\n"
            )
        elif all(map(lambda f: f is not None, (file, line, content))):
            assert file is not None
            assert line is not None
            assert content is not None
            _file = Path(file).resolve().relative_to(Path.cwd())
            self.err_msg = (
                f"{ColorStr(f'{_file}:{line + 1}', Color.YELLOW, bold=True)} "
                f"{ColorStr('error:', Color.RED, bold=True)} {msg}\n"
                f"{line + 1} | {content}"
                f"{' ' * len(str(line))} | "
                f"{ColorStr('~' * len(content.strip()), Color.GREEN)}"
            )
        else:
            self.err_msg = msg if msg is not None else ""
        super().__init__(self.err_msg)


class Parser:
    err_k = {"msg", "file", "line", "col", "content"}
    zone_meta_args = {"zone", "color", "max_drones"}
    zone_types = {"normal", "blocked", "restricted", "priority"}

    def __init__(self) -> None:
        self.nb_drones = 0
        self.tokens: list[dict[str, str | int]] = []
        self.error: ErrorInfo = {
            "msg": "",
            "file": "",
            "line": 0,
            "col": 0,
            "content": "",
        }

    def parse_hub(self, val: str, type: str) -> dict[str, str | int]:
        content = self.error.get("content")
        if not isinstance(content, str) or content == "":
            raise ValueError("content must be set before parsing")
        meta: Optional[dict[str, str | int]] = None

        def parse_value(v: str) -> str | int:
            try:
                return int(v)
            except ValueError:
                return v

        if (lb := val.find("[")) != -1 and (rb := val.rfind("]")) != -1:
            if "=" not in val:
                self.error["msg"] = f"invalid metadata format '{val}'"
                raise ParserError(**self.error)
            meta = dict(
                (k, parse_value(v))
                for arg in val[lb + 1: rb].split(" ")
                for k, v in [arg.split("=")]
            )
            val = val[:lb]

        _val = [parse_value(v) for v in val.split(" ") if v]

        if len(_val) != 3:
            self.error["msg"] = "incorrect number of arguments"
            raise ParserError(**self.error)

        content_str = str(self.error.get("content", ""))
        if "-" in str(_val[0]):
            self.error["col"] = content_str.find(str(_val[0]))
            self.error["msg"] = f"invalid name '{_val[0]}'"
            raise ParserError(**self.error)

        if " " in str(_val[0]):
            self.error["col"] = content_str.find(str(_val[0]))
            self.error["msg"] = f"invalid '{_val[0]}' (spaces not allowed)"
            raise ParserError(**self.error)

        if not isinstance(_val[1], int):
            self.error["col"] = content_str.find(_val[1])
            self.error["msg"] = f"hub coordinate '{_val[1]}' should be an int"
            raise ParserError(**self.error)

        if not isinstance(_val[2], int):
            self.error["col"] = content_str.find(_val[2])
            self.error["msg"] = f"hub coordinate '{_val[2]}' should be an int"
            raise ParserError(**self.error)

        if meta and not set(meta.keys()).issubset(Parser.zone_meta_args):
            self.error["msg"] = "invalid metadata key"
            raise ParserError(**self.error)

        if (
            meta
            and "zone" in meta.keys()
            and meta["zone"] not in Parser.zone_types
        ):
            self.error["msg"] = f"invalid zone type {meta['zone']}"
            raise ParserError(**self.error)

        if (
            meta
            and "max_drones" in meta.keys()
            and not isinstance(meta["max_drones"], int)
        ):
            self.error["col"] = content_str.rfind(meta["max_drones"])
            self.error["msg"] = f"invalid int '{meta['max_drones']}'"
            raise ParserError(**self.error)

        if (
            meta
            and "max_drones" in meta.keys()
            and isinstance(meta["max_drones"], int)
            and meta["max_drones"] <= 0
        ):
            self.error["col"] = content_str.rfind(str(meta["max_drones"]))
            self.error["msg"] = "max_drones must be positive"
            raise ParserError(**self.error)

        result = {"type": type, "name": _val[0], "x": _val[1], "y": _val[2]}

        if meta:
            result.update(meta)

        return result

    def parse_connection(self, val: str) -> dict[str, str | int]:
        meta: Optional[dict[str, str | int]] = None
        if (lb := val.find("[")) != -1 and (rb := val.rfind("]")) != -1:

            def parse_value(v: str) -> str | int:
                try:
                    return int(v)
                except ValueError:
                    return v

            meta = dict(
                (k, parse_value(v))
                for arg in val[lb + 1: rb].split(" ")
                for k, v in [arg.split("=")]
            )
            val = val[:lb]

        if meta and not set(meta.keys()).issubset({"max_link_capacity"}):
            self.error["msg"] = "invalid key"
            raise ParserError(**self.error)

        if meta and "max_link_capacity" not in meta:
            self.error["msg"] = "expected max_link_capacity"
            raise ParserError(**self.error)

        if meta and not isinstance(meta["max_link_capacity"], int):
            self.error["msg"] = "max_link_capacity must be a valid int"
            raise ParserError(**self.error)

        if (
            meta
            and isinstance(meta["max_link_capacity"], int)
            and meta["max_link_capacity"] <= 0
        ):
            self.error["msg"] = "max_link_capacity must be a positive int"
            raise ParserError(**self.error)

        if "-" not in val:
            self.error["msg"] = "missing '-' separator between hubs"
            raise ParserError(**self.error)

        _val = list(map(str.strip, val.split("-")))

        if len(_val) != 2:
            self.error["msg"] = "invalid connection definition"
            raise ParserError(**self.error)

        if _val[0] not in {
            str(d["name"])
            for d in self.tokens
            if d.get("type") != "connection"
        }:
            self.error["msg"] = f"hub '{_val[0]}' not defined"
            raise ParserError(**self.error)

        if _val[1] not in {
            str(d["name"])
            for d in self.tokens
            if d.get("type") != "connection"
        }:
            self.error["msg"] = f"hub '{_val[1]}' not defined"
            raise ParserError(**self.error)

        if _val[0] == _val[1]:
            self.error["msg"] = "self-loop connections are not allowed"
            raise ParserError(**self.error)

        if tuple(sorted(_val)) in {
            tuple(sorted((str(d["from"]), str(d["to"]))))
            for d in self.tokens
            if d.get("type") == "connection"
        }:
            self.error["msg"] = "duplicate connection (A-B is the same as B-A)"
            raise ParserError(**self.error)

        result: dict[str, str | int] = {
            "type": "connection",
            "from": _val[0],
            "to": _val[1],
        }

        if meta:
            result.update(meta)

        return result

    def parse(self, file: StringPath) -> None:
        self.error["file"] = str(Path(file).resolve().relative_to(Path.cwd()))

        def check_dup(token: dict[str, str | int]) -> None:
            """Check for hubs with the same coordinates"""
            for e_tok in self.tokens:
                e_x, e_y = e_tok["x"], e_tok["y"]
                if (token["x"], token["y"]) == (e_x, e_y):
                    self.error["msg"] = "duplicate hub coordinates"
                    raise ParserError(**self.error)

        def def_col(token: dict[str, str | int]) -> None:
            """Adds (if missing) default colors depending on the hub type"""
            if (
                token["type"] in {"start_hub", "hub", "end_hub"}
                and "color" not in token
            ):
                match token['type']:
                    case 'start_hub' | 'end_hub':
                        token["color"] = "green"
                    case 'hub' if token.get('zone', None) == 'restricted':
                        token["color"] = "purple"
                    case 'hub' if token.get('zone', None) == 'priority':
                        token["color"] = "cyan"
                    case 'hub' if token.get('zone', None) == 'blocked':
                        token["color"] = "red"
                    case 'hub' if token.get('zone', None) in {None, 'normal'}:
                        token['color'] = 'blue'

        with open(file) as fp:
            for i, line in enumerate(fp):
                self.error["line"] = i
                self.error["content"] = line

                if (comment := line.find("#")) != -1:
                    line = line[:comment]

                if line == "" or line == "\n":
                    continue

                if ":" not in line:
                    self.error["msg"] = "missing ':' separator"
                    raise ParserError(**self.error)

                if line.count(":") != 1:
                    self.error["msg"] = "duplicate ':' separator"
                    self.error["col"] = line.find(":") + 1
                    raise ParserError(**self.error)

                key, val = map(str.strip, line.split(":"))

                if val == "":
                    self.error["msg"] = "incorrect line formatting"
                    raise ParserError(**self.error)

                match key:
                    case "nb_drones":
                        if len(self.tokens):
                            self.error["msg"] = "nb_drones should be first"
                            raise ParserError(**self.error)

                        if self.nb_drones != 0:
                            self.error["msg"] = "duplicate nb_drones"
                            raise ParserError(**self.error)
                        try:
                            nb_drones_int = int(val)
                        except ValueError as err:
                            self.error["msg"] = str(err)
                            raise ParserError(**self.error)

                        if nb_drones_int <= 0:
                            self.error["msg"] = (
                                f"negative nb_drones '{nb_drones_int}'"
                            )
                            raise ParserError(**self.error)

                        self.nb_drones = nb_drones_int

                    case "start_hub":
                        if "start_hub" in {
                            str(d["type"]) for d in self.tokens
                        }:
                            self.error["msg"] = "duplicate start_hub"
                            raise ParserError(**self.error)
                        hub_val = self.parse_hub(val, "start_hub")
                        check_dup(hub_val)
                        def_col(hub_val)
                        self.tokens.append(hub_val)

                    case "end_hub":
                        if "end_hub" in {str(d["type"]) for d in self.tokens}:
                            self.error["msg"] = "duplicate end_hub"
                            raise ParserError(**self.error)
                        hub_val = self.parse_hub(val, "end_hub")
                        check_dup(hub_val)
                        def_col(hub_val)
                        self.tokens.append(hub_val)

                    case "hub":
                        hub_val = self.parse_hub(val, "hub")
                        if hub_val["name"] in {
                            str(h["name"]) for h in self.tokens
                        }:
                            self.error["msg"] = "duplicate hub name"
                            raise ParserError(**self.error)
                        check_dup(hub_val)
                        def_col(hub_val)
                        self.tokens.append(hub_val)

                    case "connection":
                        conn_val = self.parse_connection(val)
                        self.tokens.append(conn_val)

                    case _:
                        self.error["msg"] = f"invalid key {key}"
                        raise ParserError(**self.error)

        if "connection" not in {d.get("type") for d in self.tokens}:
            raise ParserError(msg="Missing connection")

        hub_types = {str(d["type"]) for d in self.tokens}

        if "start_hub" not in hub_types:
            self.error["msg"] = "missing start_hub"
            raise ParserError(**self.error)

        if "end_hub" not in hub_types:
            self.error["msg"] = "missing end_hub"
            raise ParserError(**self.error)
