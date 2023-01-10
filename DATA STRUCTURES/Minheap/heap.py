from typing import List


# min heap
class Heap:
    data = None

    def __init__(self, array: List = None):
        if array:
            self.data = self.heapify(array)
        else:
            self.data = []

    def add(self, value):
        self.data.append(value)
        if len(self.data) != 1:  # if not parent
            # swap with parent until minheap condition satisfies
            index = len(self.data) - 1
            while (index-1) // 2 >= 0 and self.data[index] < self.data[(index - 1) // 2]:
                # swap value with child value
                self.data[(index - 1) // 2], self.data[index] = self.data[index], self.data[(index - 1) // 2]
                index = (index - 1) // 2

    def pop(self):
        if len(self.data) == 0:
            return None
        elem = self.data[0]
        self.data[0] = self.data[len(self.data) - 1]
        self.data.pop()
        index = 0
        # swap with a child with min(children) until minheap condition satisfies
        while index * 2 + 1 < len(self.data):  # either one child exist
            # swap value with min child value
            if index * 2 + 2 < len(self.data) and index * 2 + 1 < len(self.data):  # both child exit
                # either one child has less value than at index
                if min(self.data[index * 2 + 2], self.data[index * 2 + 1]) < self.data[index]:
                    if self.data[index * 2 + 2] < self.data[index * 2 + 1]:
                        self.data[index * 2 + 2], self.data[index] = self.data[index], self.data[index * 2 + 2]
                        index = index * 2 + 2
                    else:
                        self.data[index * 2 + 1], self.data[index] = self.data[index], self.data[index * 2 + 1]
                        index = index * 2 + 1
                else:  # min heap satisfied
                    break
            else:  # either one child exist
                if index * 2 + 2 < len(self.data) and self.data[index * 2 + 2] < self.data[index]:
                    self.data[index * 2 + 2], self.data[index] = self.data[index], self.data[index * 2 + 2]
                    index = index * 2 + 2
                elif self.data[index * 2 + 1] < self.data[index]:
                    self.data[index * 2 + 1], self.data[index] = self.data[index], self.data[index * 2 + 1]
                    index = index * 2 + 1
                else:  # either one child exist and none are smaller
                    break

        return elem

    @staticmethod
    def heapify(arr: List) -> List:
        if not arr or len(arr) == 0:
            return []
        if len(arr) == 1:
            return arr.copy()
        array = arr.copy()
        i = ((len(array) - 1) - 1) // 2
        while i >= 0:
            index = i
            # swap with a child with min(children) until minheap condition satisfies
            while index * 2 + 1 < len(array):  # either one child exist
                # swap value with min child value
                if index * 2 + 2 < len(array) and index * 2 + 1 < len(array):  # both child exit
                    # either one child has less value than at index
                    if min(array[index * 2 + 2], array[index * 2 + 1]) < array[index]:
                        if array[index * 2 + 2] < array[index * 2 + 1]:
                            array[index * 2 + 2], array[index] = array[index], array[index * 2 + 2]
                            index = index * 2 + 2
                        else:
                            array[index * 2 + 1], array[index] = array[index], array[index * 2 + 1]
                            index = index * 2 + 1
                    else:  # min heap satisfied
                        break
                else:  # either one child exist
                    if index * 2 + 2 < len(array) and array[index * 2 + 2] < array[index]:
                        array[index * 2 + 2], array[index] = array[index], array[index * 2 + 2]
                        index = index * 2 + 2
                    elif array[index * 2 + 1] < array[index]:
                        array[index * 2 + 1], array[index] = array[index], array[index * 2 + 1]
                        index = index * 2 + 1
                    else:  # either one child exist and none are smaller
                        break

            i -= 1

        return array
