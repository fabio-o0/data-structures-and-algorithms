void insertionSort(int* arr, int n) {
    for (unsigned int i = 1; i < n; i++) {
        int j = i;
        while (j > 0 and arr[j - 1] > arr[j]) {
            std::swap(arr[j - 1], arr[j]);
            j--;
        }
    }
}
