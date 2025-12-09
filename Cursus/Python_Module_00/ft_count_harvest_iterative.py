def ft_count_harvest_iterative():
    harvest_day = int(input("Days until harvest: "))
    for day in range(harvest_day):
        print(f"Day {day + 1}")
    print("Harvest time!")
