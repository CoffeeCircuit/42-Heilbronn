"""
Directory: ex4/
Files to Submit: ft_crisis_response.py
Authorized: open(), read(), write(), with statement, try/except, print()
"""

from io import TextIOWrapper


def ft_crisis_response():
    """
    Handling multiple IO errors
    """
    print("=== CYBER ARCHIVES - CRISIS RESPONSE SYSTEM ===\n")
    print("CRISIS ALERT: Attempting access to 'lost_archive.txt'...")

    fp: TextIOWrapper | None = None

    try:
        with open("lost_archive.txt") as fp:
            fp.read()
    except FileNotFoundError:
        print("RESPONSE: Archive not found in storage matrix")
    finally:
        if fp is None or fp.closed:
            print("STATUS: Crisis handled, system stable\n")

    print("CRISIS ALERT: Attempting access to 'classified_vault.txt'...")
    try:
        with open("classified_vault.txt", "w") as fp:
            fp.write("clasified")
    except PermissionError:
        print("RESPONSE: Security protocols deny access")
    finally:
        if fp is None or fp.closed:
            print("STATUS: Crisis handled, security maintained\n")

    print("ROUTINE ACCESS: Attempting access to 'standard_archive.txt'...")
    try:
        with open("standard_archive.txt", "r+") as fp:
            print(f"SUCCESS: Archive recovered - ``{fp.read()}''")
    except FileNotFoundError:
        print("RESPONSE: Archive not found in storage matrix")
    finally:
        if fp is None or fp.closed:
            print("STATUS: Normal operations resumed\n")
    print("All crisis scenarios handled successfully. Archives secure.")


if __name__ == "__main__":
    ft_crisis_response()
