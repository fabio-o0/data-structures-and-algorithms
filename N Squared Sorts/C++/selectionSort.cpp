void selectionSort(int* arr, int n) {
  for (unsigned int i = 0; i < n - 1; i ++) {
    int min = i;
    for (unsigned int j = i + 1; j < n; j++) {
      if (arr[j] < arr[min]) min = j;
    }
    std::swap(arr[min], arr[i]);
  }
}
