import os
import json
import tempfile

from src.pac_man.highscore import Highscore


def _write_temp_json(content: str) -> str:
    fd, path = tempfile.mkstemp(suffix=".json")
    with os.fdopen(fd, "w") as f:
        f.write(content)
    return path


def _write_temp_highscore(entries: list[dict]) -> str:
    path = tempfile.mktemp(suffix=".json")
    with open(path, "w") as f:
        json.dump(entries, f)
    return path


def test_load_valid_file() -> None:
    path = _write_temp_highscore([
        {"name": "Alice", "score": 500},
        {"name": "Bob", "score": 1000},
    ])
    try:
        hs = Highscore(path)
        hs.load()
        top = hs.entries
        assert len(top) == 2
        assert top[0]["name"] == "Bob"
        assert top[0]["score"] == 1000
        assert top[1]["score"] == 500
    finally:
        os.unlink(path)


def test_load_missing_file() -> None:
    hs = Highscore("/nonexistent/path/highscore.json")
    hs.load()
    assert hs.entries == []


def test_load_invalid_json() -> None:
    path = _write_temp_json("{bad json}")
    try:
        hs = Highscore(path)
        hs.load()
        assert hs.entries == []
    finally:
        os.unlink(path)


def test_load_invalid_format() -> None:
    path = _write_temp_json('"not a list"')
    try:
        hs = Highscore(path)
        hs.load()
        assert hs.entries == []
    finally:
        os.unlink(path)


def test_add_and_sort() -> None:
    hs = Highscore()
    hs.add("Alice", 500)
    hs.add("Bob", 1000)
    hs.add("Charlie", 750)
    top = hs.entries
    assert top[0]["name"] == "Bob"
    assert top[1]["name"] == "Charlie"
    assert top[2]["name"] == "Alice"


def test_cap_to_top_10() -> None:
    hs = Highscore()
    for i in range(15):
        hs.add(f"Player{i}", i * 100)
    assert len(hs.entries) == 10
    assert hs.entries[0]["score"] == 1400


def test_validate_name_strips_special_chars() -> None:
    hs = Highscore()
    hs.add("Al!ce#123", 100)
    assert hs.entries[0]["name"] == "Alce123"


def test_validate_name_max_10_chars() -> None:
    hs = Highscore()
    hs.add("ABCDEFGHIJKLM", 100)
    assert len(hs.entries[0]["name"]) == 10
    assert hs.entries[0]["name"] == "ABCDEFGHIJ"


def test_negative_score_clamped() -> None:
    hs = Highscore()
    hs.add("Test", -50)
    assert hs.entries[0]["score"] == 0


def test_save_and_reload() -> None:
    path = tempfile.mktemp(suffix=".json")
    try:
        hs = Highscore(path)
        hs.add("Alice", 500)
        hs.add("Bob", 1000)
        hs.save()

        hs2 = Highscore(path)
        hs2.load()
        top = hs2.entries
        assert len(top) == 2
        assert top[0]["name"] == "Bob"
        assert top[0]["score"] == 1000
    finally:
        if os.path.exists(path):
            os.unlink(path)
