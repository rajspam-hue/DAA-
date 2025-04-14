#include <iostream>
#include <vector>
#include <algorithm>  // for shuffle and swap
#include <random>     // for random number generator

#define SWITCH_THRESHOLD 16  // Threshold to switch to Merge Sort

using namespace std;

// Merge function for Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < L.size() && j < R.size()) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

// Merge Sort implementation
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Partition function for Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Hybrid Quick Sort (uses Merge Sort for small partitions)
void hybridQuickSort(vector<int>& arr, int low, int high) {
    while (low < high) {
        if (high - low + 1 <= SWITCH_THRESHOLD) {
            mergeSort(arr, low, high);
            return;
        }

        int pivotIndex = partition(arr, low, high);

        // Recur on smaller partition first for optimization
        if (pivotIndex - low < high - pivotIndex) {
            hybridQuickSort(arr, low, pivotIndex - 1);
            low = pivotIndex + 1;
        } else {
            hybridQuickSort(arr, pivotIndex + 1, high);
            high = pivotIndex - 1;
        }
    }
}

// Utility to print the array
void printArray(const vector<int>& arr) {
    for (int num : arr) cout << num << " ";
    cout << endl;
}

// Main function
int main() {
    vector<int> arr(100);

    // Step 1: Fill with 1 to 100
    for (int i = 0; i < 100; i++) {
        arr[i] = i + 1;
    }

    // Step 2: Shuffle the array
    random_device rd;
    mt19937 g(rd());
    shuffle(arr.begin(), arr.end(), g);

    // Step 3: Print unsorted array
    cout << "Unsorted array:" << endl;
    printArray(arr);

    // Step 4: Sort using hybrid quick/merge sort
    hybridQuickSort(arr, 0, arr.size() - 1);

    // Step 5: Print sorted array
    cout << "\nSorted array:" << endl;
    printArray(arr);

    return 0;
}