int quickPartition(int* arr, int low, int high) {
  int pivot = arr[high];
  int index = low - 1;

  for (unsigned int i = low; i < high; i++) {
    if (arr[i] < pivot) {
      index++;
      std::swap(arr[index], arr[i]);
    }
  }

  std::swap(arr[index + 1], arr[high]);
  return index + 1;
}

void quicksort(int* arr, int low, int high) {
  if (low < high) {
    int partition = quickPartition(arr, low, high);

    quicksort(arr, low, partition - 1);
    quicksort(arr, partition + 1, high);
  }
 }
