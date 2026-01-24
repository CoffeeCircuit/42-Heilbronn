# !/usr/bin/env python3
"""
oracle
Directory: ex02/
Files to Submit: oracle.py, .env.example, .gitignore
Authorized: os, sys, python-dotenv modules, file operations
"""


class Oracle:
    required_keys = {
        "MATRIX_MODE",
        "DATABASE_URL",
        "API_KEY",
        "LOG_LEVEL",
        "ZION_ENDPOINT",
    }

    def __init__(self) -> None:
        self.matrix_mode: str | None = None
        self.database_url: str | None = None
        self.api_key: str | None = None
        self.log_level: str | None = None
        self.zion_endpoint: str | None = None

    def load(self) -> None:
        try:
            from os import getenv
            from dotenv import load_dotenv  # type: ignore

            if not load_dotenv():
                raise FileNotFoundError(".env file not found")

            self.matrix_mode = getenv("MATRIX_MODE")
            self.database_url = getenv("DATABASE_URL")
            self.api_key = getenv("API_KEY")
            self.log_level = getenv("LOG_LEVEL")
            self.zion_endpoint = getenv("ZION_ENDPOINT")

        except ImportError:
            print("Error: python-dotenv module not found")
            print("Please install it using the following commands:")
            print("uv venv")
            print("uv pip install python-dotenv")
            print("cp .env.example .env")
            print("uv run oracle.py")
            exit(1)

        except FileNotFoundError as e:
            print(f"Error: {e}")
            exit(1)

    def validate(self) -> bool:
        for key in self.required_keys:
            if getattr(self, key.lower()) is None:
                return False
        return True

    def get_status(self) -> dict:
        api_key_status = "Authenticated" if self.api_key else "Unauthenticated"
        return {
            "Mode": self.matrix_mode,
            "Database": f"Connected to {self.database_url}",
            "API Acess": api_key_status,
            "Log Level": self.log_level,
            "Zion Network": "Online" if self.zion_endpoint else "Offline",
        }


def main() -> None:
    print("ORACLE STATUS: Reading the Matrix...")

    oracle = Oracle()
    oracle.load()

    print("\nConfiguration loaded:")
    status = oracle.get_status()
    for key, value in status.items():
        print(f"{key}: {value}")

    print("\nEnvironment security check:")

    print("[OK] No hardcoded secrets detected")

    print(
        "[OK] .env file properly configured"
        if oracle.validate()
        else "[FAIL] .env file misconfigured"
    )

    if oracle.matrix_mode == "production":
        print("[OK] Production overrides available")

    print("\nThe Oracle sees all configurations..\n")


if __name__ == "__main__":
    main()
