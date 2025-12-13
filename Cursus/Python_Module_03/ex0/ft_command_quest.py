#!/usr/bin/env python3

from sys import argv


def ft_command_quest(argv: list[str]) -> None:
    """This program is parsing arguments"""
    print("=== Command Quest ===")
    argc = len(argv)
    if argc < 2:
        print("No arguments provided!")
        print(f"Program name: {argv[0]}")
        print("Total arguments: 1")
    else:
        i: int = 1
        print(f"Program name: {argv[0]}")
        print(f"Argumens received: {argc - 1}")
        while i < argc:
            print(f"Argument {i}: {argv[i]}")
            i += 1
        print(f"Total arguments: {argc}")
    print()


if __name__ == "__main__":
    ft_command_quest(argv)
