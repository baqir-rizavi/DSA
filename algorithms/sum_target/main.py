import random

arr = [random.randint(1, 50) for _ in range(70)]
target = random.randint(1, 80)


def find_target_breakers():
    diction = {}
    for i, num in enumerate(arr):
        if target - num in diction:
            return diction[target - num], i
        diction[num] = i


print(target, 'was the target')
indexes = find_target_breakers()
if indexes is not None:
    print('on indexes: ', indexes)
    print('values on indexes: ', arr[indexes[0]], arr[indexes[1]])
else:
    print('no solution found')
