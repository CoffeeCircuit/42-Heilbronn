"""
Directory: ex3/
Files to Submit: ft_vault_security.py
Authorized: open(), read(), write(), with statement, print()
"""

from io import TextIOWrapper


def ft_vault_security():
    """
    The main function for this exercise
    """
    print("=== CYBER ARCHIVES - VAULT SECURITY SYSTEM ===")
    print("Initiating secure vault access...")
    print("Vault connection established with failsafe protocols\n")

    fp: TextIOWrapper | None = None

    try:
        with open("classified_data.txt", "r+") as fp:
            print("SECURE EXTRACTION:")
            print(fp.read())

            print("\nSECURE PRESERVATION:")
            print("[CLASSIFIED] New security protocols archived")
            fp.write("\n[CLASSIFIED] New security protocols archived")

    except Exception as e:
        print(e)

    finally:
        if fp is None:
            print("Vault seal aborted: no file connection established\n")
        elif fp.closed:
            print("Vault automatically sealed upon completion\n")

    print("All vault operations completed with maximum security")


if __name__ == "__main__":
    ft_vault_security()
