import os
from src.pac_man.config import Config


def test_valid_config():
    cfg = Config()
    success = cfg.read("config.json")
    assert success is True
    assert cfg.data is not None
    assert cfg.data.width > 0
    assert cfg.data.height > 0


def test_missing_file():
    cfg = Config()
    success = cfg.read("missing.json")
    assert success is False
    assert cfg.data is None


def test_invalid_json():
    import tempfile

    with tempfile.TemporaryDirectory() as tmpdir:
        temp_path = os.path.join(tmpdir, "invalid.json")
        with open(temp_path, "w") as f:
            f.write("{invalid json}")

        cfg = Config()
        success = cfg.read(temp_path)
        assert success is False
        assert cfg.data is None
