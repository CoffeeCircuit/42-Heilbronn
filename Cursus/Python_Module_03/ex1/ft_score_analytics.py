#!/usr/bin/env python3

from sys import argv


def ft_score_analytics(argv: list[str]) -> None:
    """Program will parse a list of player scores (ints)"""
    print("=== Player Score Analytics ===")
    argc = len(argv)
    if argc < 2:
        print("No scores provided. ", end="")
        print("Usage: python3 ft_score_analytics.py <score1> <score2> ...")
    else:
        scores: list[int] = []

        try:
            scores = [int(val) for val in argv[1:]]
        except ValueError as e:
            print(e)
            print("Terminating program...")
            return

        s_len = len(scores)
        s_sum = sum(scores)
        s_max = max(scores)
        s_min = min(scores)
        s_range = s_max - s_min
        print(f"Scores processed: {scores}")
        print(f"Total players: {s_len}")
        print(f"Total score: {s_sum}")
        print(f"Average score: {s_sum/s_len}")
        print(f"High score: {s_max}")
        print(f"Low score: {s_min}")
        print(f"Score range: {s_range}")


if __name__ == "__main__":
    ft_score_analytics(argv)
