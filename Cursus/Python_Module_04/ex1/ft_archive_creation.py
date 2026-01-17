"""
Directory: ex1/
Files to Submit: ft_archive_creation.py
Authorized: open(), write(), close(), print()
"""

from io import TextIOWrapper


def ft_archive_creation():
    print("=== CYBER ARCHIVES - PRESERVATION SYSTEM ===\n")
    print("Initializing new storage unit: new_discovery.txt")
    fp: TextIOWrapper | None = None
    try:
        fp = open("new_discovery.txt", "x")
        print("Storage unit created successfully...")
        print("\nInscribing preservation data...")
        discoveries = (
            "New quantum algorithm discovered",
            "Efficiency increased by 347%",
            "Archived by Data Archivist trainee",
        )
        i = 1
        for discovery in discoveries:
            msg = f"[ENTRY {i:0>3}] {discovery}"
            print(msg)
            fp.write(msg + "\n")
            i += 1
        print("\nData inscription complete. Storage unit sealed.")
        print("Archive 'new_discovery.txt' ready for long-term preservation.")
    except FileExistsError:
        msg = "ERROR: Storage unit new_discovery.txt already exists. "
        msg += "Overwriting not allowed"
        print(msg)
    finally:
        if fp is not None:
            fp.close()


if __name__ == "__main__":
    ft_archive_creation()
