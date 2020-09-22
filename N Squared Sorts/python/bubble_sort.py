def bubbleSort(array):
    end = len(array) - 1
    Sorted = False
    while not Sorted:
        Sorted = True
        for i in range(end):
            if array[i] > array[i + 1]:
                array[i], array[i + 1] = array[i + 1], array[i]
                Sorted = False
        end -= 1
    return array
