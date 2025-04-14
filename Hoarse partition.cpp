#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#define SWITCH_THRESHOLD 16

using namespace std;

// Median-of-three function to choose better pivot
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;

    if (arr[high] < arr[low])
        swap(arr[low], arr[high]);
    if (arr[mid] < arr[low])
        swap(arr[mid], arr[low]);
    if (arr[high] < arr[mid])
        swap(arr[mid], arr[high]);

    // Use middle element as pivot
    swap(arr[mid], arr[low]);
    return arr[low];
}

// Hoare's partitioning
int hoarePartition(vector<int>& arr, int low, int high) {
    int pivot = medianOfThree(arr, low, high);
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}

// Merge function
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

// Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Hybrid Quick Sort using Hoare and Median-of-Three
void hybridQuickSort(vector<int>& arr, int low, int high) {
    while (low < high) {
        if (high - low + 1 <= SWITCH_THRESHOLD) {
            mergeSort(arr, low, high);
            return;
        }

        int pivotIndex = hoarePartition(arr, low, high);

        // Recur on smaller half first (tail call optimization)
        if (pivotIndex - low < high - pivotIndex) {
            hybridQuickSort(arr, low, pivotIndex);
            low = pivotIndex + 1;
        } else {
            hybridQuickSort(arr, pivotIndex + 1, high);
            high = pivotIndex;
        }
    }
}

// Print utility
void printArray(const vector<int>& arr) {
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> arr(100);

    // Fill with 1 to 100
    for (int i = 0; i < 100; i++) {
        arr[i] = i + 1;
    }

    // Shuffle for unsorted input
    random_device rd;
    mt19937 g(rd());
    shuffle(arr.begin(), arr.end(), g);

    cout << "Unsorted array:\n";
    printArray(arr);

    hybridQuickSort(arr, 0, arr.size() - 1);

    cout << "\nSorted array:\n";
    printArray(arr);

    return 0;
}