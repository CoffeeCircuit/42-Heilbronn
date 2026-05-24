import os
import json
import tempfile

from src.pac_man.config import Config


def _write_temp_json(content: str) -> str:
    fd, path = tempfile.mkstemp(suffix=".json")
    with os.fdopen(fd, "w") as f:
        f.write(content)
    return path


def test_valid_config() -> None:
    cfg = Config()
    success = cfg.read("config.json")
    assert success is True
    assert cfg.data is not None
    assert cfg.data.width > 0
    assert cfg.data.height > 0


def test_missing_file() -> None:
    cfg = Config()
    success = cfg.read("missing.json")
    assert success is False


def test_invalid_json() -> None:
    path = _write_temp_json("{invalid json}")
    try:
        cfg = Config()
        success = cfg.read(path)
        assert success is False
    finally:
        os.unlink(path)


def test_comment_stripping() -> None:
    path = _write_temp_json(
        '{\n# comment\n"width": 10,\n// c++ comment\n"height": 12\n}'
    )
    try:
        cfg = Config()
        success = cfg.read(path)
        assert success is True
        assert cfg.data is not None
        assert cfg.data.width == 10
        assert cfg.data.height == 12
    finally:
        os.unlink(path)


def test_missing_keys_use_defaults() -> None:
    path = _write_temp_json('{"width": 10, "height": 12}')
    try:
        cfg = Config()
        success = cfg.read(path)
        assert success is True
        assert cfg.lives == 3
        assert cfg.seed == 42
        assert cfg.points_per_pacgum == 10
    finally:
        os.unlink(path)


def test_clamping() -> None:
    path = _write_temp_json(
        json.dumps({"width": 1, "height": 1, "lives": -5, "level_max_time": 1})
    )
    try:
        cfg = Config()
        success = cfg.read(path)
        assert success is True
        assert cfg.data is not None
        assert cfg.data.width == 5
        assert cfg.data.height == 5
        assert cfg.data.lives == 1
        assert cfg.data.level_max_time == 10
    finally:
        os.unlink(path)


def test_unknown_keys_ignored() -> None:
    path = _write_temp_json(
        json.dumps({"width": 10, "height": 12, "unknown_key": "value"})
    )
    try:
        cfg = Config()
        success = cfg.read(path)
        assert success is True
    finally:
        os.unlink(path)
