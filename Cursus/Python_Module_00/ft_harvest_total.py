def ft_harvest_total():
    day = 0
    day_3 = 3
    total_harvest = 0
    while day < day_3:
        days_harvest = int(input(f"Day {day + 1} harvest: "))
        total_harvest += days_harvest
        day += 1
    print(f"Total harvest: {total_harvest}")
