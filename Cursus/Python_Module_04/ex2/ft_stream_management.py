"""
Directory: ex2/
Files to Submit: ft_stream_management.py
Authorized: sys.stdin, sys.stdout, sys.stderr, input(), print(), import sys
"""

from sys import stdin, stdout, stderr


def palrt(msg: str) -> None:
    """
    prints to stderr

    :param msg: The message to print to stderr
    :type msg: str
    """
    stderr.write("[ALERT] " + msg)


def pstd(msg: str) -> None:
    """
    prints to stdout

    :param msg: The message to print to stdout
    :type msg: str
    """
    stdout.write("[STANDARD] " + msg)


def ft_stream_management():
    """
    The main function
    """
    print("=== CYBER ARCHIVES - COMMUNICATION SYSTEM ===\n")
    id = input("Input Stream active. Enter archivist ID: ")
    print("Input Stream active. Enter status report: ", end="")
    status = stdin.readline().strip()
    print()
    pstd(f"Archive status from {id}: {status}\n")
    palrt("System diagnostic: Communication channels verified\n")
    pstd("Data transmision complete\n")
    print("\nThree-channel communication test successful.")


if __name__ == "__main__":
    ft_stream_management()
