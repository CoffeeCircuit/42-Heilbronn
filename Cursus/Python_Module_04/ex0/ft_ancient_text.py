"""
Directory: ex0/
Files to Submit: ft_ancient_text.py
Authorized: open(), read(), close(), print()
"""

from io import TextIOWrapper


def ft_ancient_text():
    print("=== CYBER ARCHIVES - DATA RECOVERY SYSTEM ===")
    print("\nAccessing Storage Vault: ancient_fragment.txt")
    fp: TextIOWrapper | None = None
    try:
        fp = open("ancient_fragment.txt")
        print("Connection established...")
        print("\nRECOVERED DATA:")
        print(fp.read())
        print("\nData recovery complete. Storage unit disconnected.")
    except FileNotFoundError:
        print("ERROR: Storage vault not found")
    finally:
        if fp:
            fp.close()


if __name__ == "__main__":
    ft_ancient_text()
