"""
construct
Directory: ex0/
Files to Submit: construct.py
Authorized: sys, os, site modules, print()
"""

import sys
import os
import site


def construct() -> None:
    """
    Function checks if running in venv
    """

    def in_venv() -> bool:
        """
        Checks if in venv

        :return: True if in a virtual env
        :rtype: bool
        """
        if sys.prefix != sys.base_prefix:
            return True
        if hasattr(sys, "real_prefix"):
            return True
        if "VIRTUAL_ENV" in os.environ:
            return True
        return False

    def venv_name() -> str:
        """
        Gets the name of the venv

        :return: Description
        :rtype: str
        """
        return os.path.basename(sys.prefix)

    def site_packages_path() -> str:
        """
        Gets venv package installation path

        :return: Description
        :rtype: str
        """
        paths = site.getsitepackages()
        return paths[0] if paths else "Unknown"

    if not in_venv():
        print("MATRIX STATUS: You're still plugged in\n")

        print(f"Current Python: {sys.executable}")
        print("Virtual Environment: None detected\n")

        print("WARNING: You're in the global environment!")
        print("The machines can see everything you install.\n")

        print("To enter the construct, run:")
        print("python -m venv matrix_env")
        print("source matrix_env/bin/activate # On Unix")
        print("matrix_env")
        print("Scripts")
        print("activate # On Windows\n")

        print("Then run this program again.")

    else:
        print("MATRIX STATUS: Welcome to the construct\n")

        print(f"Current Python: {sys.executable}")
        print(f"Virtual Environment: {venv_name()}")
        print(f"Environment Path: {sys.prefix}\n")

        print("SUCCESS: You're in an isolated environment!")
        print("Safe to install packages without affecting")
        print("the global system.\n")

        print("Package installation path:")
        print(site_packages_path())


if __name__ == "__main__":
    construct()
