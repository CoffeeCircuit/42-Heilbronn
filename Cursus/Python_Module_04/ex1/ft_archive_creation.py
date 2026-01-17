"""
Directory: ex1/
Files to Submit: ft_archive_creation.py
Authorized: open(), write(), close(), print()
"""


def ft_archive_creation():
    print("=== CYBER ARCHIVES - PRESERVATION SYSTEM ===")

    print("Initializing new storage unit: new_discovery.txt")
    print("Storage unit created successfully...")

    print("\nInscribing preservation data...")
    fp = open("new_discovery.txt", "w")
    discoveries = (
        "New quantum algorithm discovered",
        "Efficiency increased by 347%",
        "Archived by Data Archivist trainee",
    )
    i = 1
    for i, discovery in enumerate(discoveries):
        msg = f"[ENTRY {i:0>3}] {discovery}"
        print(msg)
        fp.write(msg + "\n")
    fp.close()
    print("\nData inscription complete. Storage unit sealed.")
    print("Archive 'new_discovery.txt' ready for long-term preservation.")


if __name__ == "__main__":
    ft_archive_creation()
