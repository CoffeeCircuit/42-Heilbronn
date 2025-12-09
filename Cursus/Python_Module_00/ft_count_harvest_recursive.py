def print_harvest_rec(days: int):
    if days == 0:
        return
    print_harvest_rec(days - 1)
    print(f"Days {days}")


def ft_count_harvest_recursive():
    harvest_day = int(input("Days until harvest: "))
    print_harvest_rec(harvest_day)
    print("Harvest time!")
