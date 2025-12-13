#!/usr/bin/env python3

from sys import argv


def main(argv: list[str]):
    argc = len(argv)
    i = 0
    if argc > 1:
        i = 1
    print("=== Command Quest ===")
    print(f"Program name      : {argv[0]}")
    print(f"Argumens received : {len(argv[1:])}")
    while i < argc:
        print(f"Argument {i:<8} : {argv[i]}")
        i += 1
    print(f"Total arguments   : {argc}")


if __name__ == "__main__":
    main(argv)
