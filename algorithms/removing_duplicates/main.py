#a program for removing all of the duplicates in an array (using hashmap)
import random

arr = [random.randint(1, 20) for _ in range(30)]


def remove_duplicates():
    diction = {}
    new = []
    for i, num in enumerate(arr):
        if num not in diction:
            diction[num] = i
            new.append(num)
    return new


print(arr)
print(remove_duplicates())
print('to check: ')
print(set(arr))
