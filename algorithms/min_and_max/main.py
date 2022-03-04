#minimum and maximum value from an array
import random

arr = [random.randint(1, 10000) for _ in range(40)]


def min_and_max():
    mini = arr[0]
    maxi = arr[0]
    for num in arr:
        if num > maxi:
            maxi = num
        if num < mini:
            mini = num
    return mini, maxi


print('min: ', min_and_max()[0], 'max: ', min_and_max()[1])
print('check by default functions : ', min(arr), max(arr))
