import json
import re


class Highscore:
    def __init__(self, filename: str = "highscore.json") -> None:
        self.filename = filename
        self.entries: list[dict[str, str | int]] = []

    def load(self) -> None:
        """Load highscores from file. Clears entries on error."""
        try:
            with open(self.filename) as fp:
                data = json.load(fp)
            if not isinstance(data, list):
                print(
                    f"Warning: invalid highscore format "
                    f"in '{self.filename}'"
                )
                self.entries = []
                return
            self.entries = [
                e for e in data
                if isinstance(e, dict)
                and isinstance(e.get("name"), str)
                and isinstance(e.get("score"), int)
                and e["score"] >= 0
            ]
            self.entries.sort(key=lambda e: e["score"], reverse=True)
            self.entries = self.entries[:10]
        except FileNotFoundError:
            self.entries = []
        except json.JSONDecodeError:
            print(f"Warning: invalid JSON in '{self.filename}'")
            self.entries = []
        except Exception as e:
            print(f"Warning: failed to load highscores - {e}")
            self.entries = []

    def save(self) -> None:
        """Save top 10 highscores to file."""
        try:
            with open(self.filename, "w") as fp:
                json.dump(self.entries[:10], fp, indent=4)
        except Exception as e:
            print(f"Error: failed to save highscores - {e}")

    def add(self, name: str, score: int) -> None:
        """Add a new entry, re-sort, and cap to top 10."""
        name = self._validate_name(name)
        score = max(score, 0)
        self.entries.append({"name": name, "score": score})
        self.entries.sort(key=lambda e: e["score"], reverse=True)
        self.entries = self.entries[:10]

    def _validate_name(self, name: str) -> str:
        """Strip to max 10 chars, keep only alphanumeric and spaces."""
        name = re.sub(r"[^a-zA-Z0-9 ]", "", name)
        return name[:10].strip()
