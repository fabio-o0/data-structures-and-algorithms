def selectionSort(array):
    for i in range(len(array) - 1):
        curMin = i
        for j in range(i + 1, len(array)):
            if array[j] < array[curMin]:
                curMin = j
        if curMin != i:
            array[i], array[curMin] = array[curMin], array[i]
    return array
