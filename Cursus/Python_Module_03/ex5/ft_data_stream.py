#!/usr/bin/env python3
"""
Exercise 5: Stream Wizard
Authorized: yield, next(), iter(), range(), len(), print(), for loops
"""


def event_gen(n: int):
    players = ("alice", "bob", "charlie", "diana", "eve", "frank")
    levels = [0] * len(players)
    scores = [0] * len(players)

    events = (
        "killed monster",
        "found treasure",
        "leveled up",
        "died",
        "logged in",
        "logged out",
    )

    for i in range(n):
        pid = i % len(players)
        event_type = events[i % len(events)]

        if event_type == "leveled up":
            levels[pid] += 1

        score_delta = (i * 13) % 500
        scores[pid] += score_delta

        yield {
            "event": i + 1,
            "player": players[pid],
            "event_type": event_type,
            "level": levels[pid],
            "score_delta": score_delta,
            "total_score": scores[pid],
            "zone": f"pixel_zone_{(i % 5) + 1}",
        }


def fib_gen(n):
    i = 0
    j, k = 0, 1
    while i < n:
        yield j
        j, k = k, j + k
        i += 1


def prime_gen(n):
    i = 2
    k = 0
    while k < n:
        if i == 2:
            k += 1
            yield i
        else:
            is_prime = True
            j = i - 1
            while j > 1:
                if i % j == 0:
                    is_prime = False
                    break
                j -= 1
            if is_prime is True:
                k += 1
                yield i
            else:
                i += 1
                continue
        i += 1


def ft_data_stream():
    print("=== Game Data Stream Processor ===\n")
    print("Processing 1000 game events...\n")

    events = event_gen(1000)

    total_events = 0
    high_level = 0
    treasure_events = 0
    level_up_events = 0

    for event in events:
        total_events += 1
        if event["level"] >= 10:
            high_level += 1
        if event["event_type"] == "found treasure":
            treasure_events += 1
        if event["event_type"] == "leveled up":
            level_up_events += 1
        print(
            f'Event {event["event"]}: Player {event["player"]} '
            f'(level {event["level"]}) {event["event_type"]}'
        )

    print("\n=== Stream Analytics ===")
    print("Total events processed:", total_events)
    print("High-level players (10+):", high_level)
    print("Treasure events:", treasure_events)
    print("Level-up events:", level_up_events)

    print("\n=== Generator Demonstration ===")
    print("Fibonacci sequence (first 10): ", end="")
    for num in fib_gen(10):
        print(num, end=", ")
    print()

    print("Prime numbers (first 5): ", end="")
    for num in prime_gen(5):
        print(num, end=", ")
    print()


if __name__ == "__main__":
    ft_data_stream()
