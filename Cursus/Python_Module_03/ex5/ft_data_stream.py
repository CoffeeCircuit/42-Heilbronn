#!/usr/bin/env python3
"""
Exercise 5: Stream Wizard
Authorized: yield, next(), iter(), range(), len(), print(), for loops
"""

from sys import argv


def fib(n):
    i = 0
    j, k = 0, 1
    while i < n:
        yield j
        j, k = k, j + k
        i += 1


def prime(n):
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


def ft_data_stream(argv):

    print("=== Generator Demonstration ===")

    for arg in argv[1][2:-2].split("}, {"):
        print(arg)
        print()

    print("Fibonacci sequence (first 10): ", end="")
    fib_nums = fib(10)
    for num in fib_nums:
        print(num, end=", ")
    print()
    print("Prime numbers (first 5): ", end="")
    prime_nums = prime(5)
    for num in prime_nums:
        print(num, end=", ")
    print()


if __name__ == "__main__":
    ft_data_stream(argv)
