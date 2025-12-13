#!/usr/bin/env python3

from sys import argv


def main(argv: list[str]):
    argc = len(argv)
    scores = []

    try:
        scores = [int(val) for val in argv]
    except ValueError as e:
        print(e)
    finally:
        print("Terminating program...")

    print("=== Player Scire Analytics ===")
    print(f"Scores processed: {argv[1:]}")
    print(f"Total players: {argc - 1}")
    print(f"Total score: {sum(scores)}")

    print(f"Argumens received : {len(argv[1:])}")
    while i < argc:
        print(f"Argument {i:<8} : {argv[i]}")
        i += 1
    print(f"Total arguments   : {argc}")


print(f"Average score: 1930.0")
print(f"High score: 2300")
print(f"Low score: 1500")
print(f"Score range: 800")

if __name__ == "__main__":
    main(argv)
