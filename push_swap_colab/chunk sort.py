from random import randint

def namestr(obj, namespace):
    return [name for name in namespace if namespace[name] is obj]

def pa(A, B):
    if B:
        A.insert(0, B.pop(0))

def pb(A, B):
    if A:
        B.insert(0, A.pop(0))

def ra(stack):
    if stack:
        stack.append(stack.pop(0))

def rra(stack):
    if stack:
        stack.insert(0, stack.pop())


def rrb(stack):
    if stack:
        stack.insert(0, stack.pop())


def rb(stack):
    if stack:
        stack.append(stack.pop(0))

def find_next_in_chunk(stack, chunk):
    for i, val in enumerate(stack):
        if val in chunk:
            return i
    return -1

def find_max_index(stack):
    return max(range(len(stack)), key=lambda i: stack[i])

def chunk_sort(A, chunk_count=5):
    ops = 0
    size = len(A)
    B = []
    outf = open("results", "w")

    # Index mapping
    sorted_A = sorted(A)
    A = [sorted_A.index(val) for val in A]  # Replace values with indexes

    # Define chunks
    chunk_size = size // chunk_count
    chunks = [range(i * chunk_size, (i + 1) * chunk_size) for i in range(chunk_count - 1)]
    chunks.append(range((chunk_count - 1) * chunk_size, size))  # Final chunk

    # Push chunks to B
    for chunk in chunks:
        while True:
            pos = find_next_in_chunk(A, chunk)
            if pos == -1:
                break
            if pos < len(A) // 2:
                for _ in range(pos):
                    ra(A)
                    print("ra", file=outf)
                    ops += 1
            else:
                for _ in range(len(A) - pos):
                    rra(A)
                    print("rra", file=outf)
                    ops += 1
            # Directional push
            mid = (chunk.start + chunk.stop) // 2
            if A[0] < mid:
                pb(A, B)
                print("pb", file=outf)
                rb(B)
                print("rb", file=outf)
                # rrb(B)
                ops += 2
            else:
                pb(A, B)
                print("pb", file=outf)
                ops += 1

    __B = [sorted_A[i] for i in B]
    # Push back from B to A in descending order
    while B:
        max_i = find_max_index(B)
        if max_i < len(B) // 2:
            for _ in range(max_i):
                ra(B)
                print("rb", file=outf)
                ops += 1
        else:
            for _ in range(len(B) - max_i):
                rra(B)
                print("rrb", file=outf)
                ops += 1
        pa(A, B)
        print("pa", file=outf)
        ops += 1

    # Restore original values
    A = [sorted_A[i] for i in A]
    print(f"{ops=}")
    outf.close()
    return A

from math import ceil, sqrt
from copy import deepcopy

# original = [randint(0, 500) for _ in range(100)]
original = [50, 56, 62, 68, 65, 61, 88, 58, 18, 49, 22, 89, 70, 5, 6, 71, 79, 50, 45, 95]

print(*original, sep=" ")
# sorted_A = chunk_sort(original.copy(), chunk_count=ceil(sqrt(len(original))))
c_count = int(sqrt(len(original)))
print(f"{c_count=}")
temp = deepcopy(original)
sorted_A = chunk_sort(temp, chunk_count=5)
print(sorted_A)
print("Check if sorted:", sorted_A == sorted(original))


