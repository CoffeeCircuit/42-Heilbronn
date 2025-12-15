#!/usr/bin/env python3
"""
Exercise 5: Stream Wizard
Authorized: yield, next(), iter(), range(), len(), print(), for loops
"""


def fib(series):
    yield series[-1] + series[-2]


def fib_generator():
    print("Fibonacci sequence (first 10): ", end="")
    buf = [0, 1]
    i = 0
    while i < 10:
        if i <= 1:
            print(buf[i], end=", ")
        else:
            buf = [buf[1], next(fib(buf))]
            print(buf[1], end=", ")
        i += 1


def ft_data_stream():
    # print("=== Game Data Stream Processor ===")
    # print(f"Processing 1000 game events...")
    # print(f"Event 1: Player alice (level 5) killed monster")
    # print(f"Event 2: Player bob (level 12) found treasure")
    # print(f"Event 3: Player charlie (level 8) leveled up")
    # print(f"...")
    # print(f"=== Stream Analytics ===")
    # print(f"Total events processed: 1000")
    # print(f"High-level players (10+): 342")
    # print(f"Treasure events: 89")
    # print(f"Level-up events: 156")
    # print(f"Memory usage: Constant (streaming)")
    # print(f"Processing time: 0.045 seconds")

    print("=== Generator Demonstration ===")
    fib_generator()

if __name__ == "__main__":
    ft_data_stream()
