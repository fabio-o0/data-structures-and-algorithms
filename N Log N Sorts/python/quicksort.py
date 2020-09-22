import random

def hoarePartition(array, low, high):
    pivot = array[low]
    i = low - 1
    j = high + 1
    while True:
        #wonky do while loop
        while True:
            i += 1
            if array[i] >= pivot:
                break
        while True:
            j -= 1
            if array[j] <= pivot:
                break
        if i >= j:
            return j
        array[i], array[j] = array[j], array[i]
        
def hoarePartitionR(array, low, high):
    r = random.randint(low, high)
    array[r], array[low] = array[low], array[r]
    return hoarePartition(array, low, high)
    
def quickSortHelper(array, low, high):
    if low < high:
        pivotIndex = hoarePartitionR(array, low, high)
        quickSortHelper(array, low, pivotIndex)
        quickSortHelper(array, pivotIndex + 1, high)
        
def quickSort(array):
    quickSortHelper(array, 0, len(array) - 1)
    return array
