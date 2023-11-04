#include <iostream>

template <typename T>
class ISort {
 public:
  virtual void sort(T* arr, size_t size) = 0;
  virtual ~ISort() {}
};

template <typename T>
class InsertionSort : public ISort<T> {
 public:
  void sort(T *arr, size_t size) override {
    for (size_t i = 1; i < size; i++) {
      T key = arr[i];
      size_t j = i - 1;

      // Shift elements larger than key to the right
      while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];
        j--;
      }
      arr[j + 1] = key;
    }
  }
};

template <typename T>
class HeapSort : public ISort<T> {
 public:
  void sort(T *arr, size_t size) override {
    // Build a heap from the array.
    // The last parent node is at index (size/2-1)
    for (int i = static_cast<int>(size) / 2 - 1; i >= 0; i--) {
      heapify(arr, size, i);
    }

    // One by one extract an element from root of the heap
    // ad then rebuild the heap with one fewer element.
    for (int i = static_cast<int>(size) - 1; i >= 0; i--) {
      std::swap(arr[0], arr[i]);
      heapify(arr, i, 0);
    }
  }

  private:
    // Heapify a subtree rooted with node i which is an index in arr[].
    // 'n' is the size of the heap.
    void heapify(T *arr, int n, int i) {
      int largest = i; // Initialize largest as root
      int l = 2 * i + 1;
      int r = 2 * i + 2;

      // If left child is larger than root
      if (l < n && arr[l] > arr[largest]) {
        largest = l;
      }

      // If right child is larger than largest so far
      if (r < n && arr[r] > arr[largest]) {
        largest = r;
      }

      // If largest is not root
      if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
      }
    }
};

template <typename T>
class QuickSort : public ISort<T> {
 public:
  void sort(T *arr, size_t size) override {
    if (size < 2) {
      return;
    }
    quicksort(arr, 0, size - 1);
  }

 private:
  void quicksort(T *arr, int low, int high) {
    if (low < high) {
      int pi = partition(arr, low, high);

      quicksort(arr, low, pi - 1);
      quicksort(arr, pi + 1, high);
    }
  }

  int partition(T *arr, int low, int high) {
    T pivot = median_of_three(arr, low, high);

    int i = low;
    for (int j = low; j < high; j++) {
      if (arr[j] <= pivot) {
        std::swap(arr[j], arr[i]);
        i++;
      }
    }

    //Restore the pivot after the indices have crossed.
    std::swap(arr[i], arr[high]);
    return i;
  }

  T median_of_three(T *arr, int low, int high) {
    int mid = low + (high - low) / 2; // overflow safe

    // Order the low, middle, and high elements and use the middle value as the pivot.
    if (arr[mid] < arr[low]) {
      std::swap(arr[mid], arr[low]);
    }
    if (arr[high] < arr[low]) {
      std::swap(arr[high], arr[low]);
    }
    if (arr[high] < arr[mid]) {
      std::swap(arr[high], arr[mid]);
    }

    // Place the pivot at high position.
    std::swap(arr[mid], arr[high]);
    return arr[high];
  }
};

template <typename T>
class MergeSort : public ISort<T> {
 public:
  void sort(T *arr, size_t size) override {
    mergesort(arr, 0, size - 1);
  }

 private:
  void mergesort(T *arr, int start, int end) {
    if (start >= end) {
      return;
    }
    if (end - start == 1) {
      if (arr[start] > arr[end]) {
        std::swap(arr[start], arr[end]);
      }
      return;
    }

    int mid = start + (end - start) / 2; // overflow safe

    mergesort(arr, start, mid);
    mergesort(arr, mid + 1, end);

    merge(arr, start, mid, end);
  }

  void merge(T *arr, int start, int mid, int end) {
    int lsize = mid - start + 1;
    int rsize = end - mid;

    // Create temp arrays
    T L[lsize], R[rsize];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < lsize; i++) {
      L[i] = arr[start + i];
    }
    for (int i = 0; i < rsize; i++) {
      R[i] = arr[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = start;
    while (i < lsize && j < rsize) {
      if (L[i] <= R[j]) {
        arr[k] = L[i];
        i++;
      } else {
        arr[k] = R[j];
        j++;
      }
      k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < lsize) {
      arr[k] = L[i];
      i++;
      k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < rsize) {
      arr[k] = R[j];
      j++;
      k++;
    }
  }
};

template <typename T>
void debug(T *arr, size_t size) {
  for (size_t i = 0; i < size; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

int main(int, char**){
  int data[] = {64, 34, 25, 12, 22, 11, 90};
  size_t size = sizeof(data) / sizeof(data[0]);

  // Insertion Sort
  int insertion_data[size];
  std::copy(data, data + size, insertion_data);

  InsertionSort<int> insertion;
  insertion.sort(insertion_data, size);

  std::cout << "InsertionSort:\t";
  debug(insertion_data, size);

  // Heap Sort
  int heap_data[size];
  std::copy(data, data + size, heap_data);

  HeapSort<int> heap;
  heap.sort(heap_data, size);

  std::cout << "HeapSort:\t";
  debug(heap_data, size);

  // Quick Sort
  int quick_data[size];
  std::copy(data, data + size, quick_data);

  QuickSort<int> quick;
  quick.sort(quick_data, size);

  std::cout << "QuickSort:\t";
  debug(quick_data, size);

  // Merge Sort
  int merge_data[size];
  std::copy(data, data + size, merge_data);

  MergeSort<int> merge;
  merge.sort(merge_data, size);

  std::cout << "MergeSort:\t";
  debug(merge_data, size);

  return 0;
}
