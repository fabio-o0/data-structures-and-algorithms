void bubbleSort(int* arr, int n) {
  bool sorted;
  for (unsigned int i = 0; i < n - 1; i++) {
    sorted = true;
    for (unsigned int j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
        sorted = false;
      }
    }
    if (sorted) break;
  }
}
