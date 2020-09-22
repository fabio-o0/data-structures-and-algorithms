int hoarePartition(int* arr, int low, int high) {
  int pivot = arr[low];
  int i = low - 1, j = high + 1;

  while (true) {
    do {
      i++;
    } while (arr[i] < pivot);
    do {
      j--;
    } while (arr[j] > pivot);

    if (i >= j) return j;
    std::swap(arr[i], arr[j]);
  }
}

int hoarePartitionR(int* arr, int low, int high) {
  srand(time(NULL));
  int random = low + rand() % (high - low);
  std::swap(arr[random], arr[low]);
  return hoarePartition(arr, low, high);
}

void hoareQuicksort(int* arr, int low, int high) {
  if (low < high) {
    int pivotIndex = hoarePartitionR(arr, low, high);
    
    hoareQuicksort(arr, low, pivotIndex);
    hoareQuicksort(arr, pivotIndex + 1, high);
  }
}
