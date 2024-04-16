#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <omp.h>

using namespace std;

// Function to generate random array
void generateRandomArray(vector<int>& arr, int size) {
    srand(time(nullptr));
    for (int i = 0; i < size; ++i) {
        arr.push_back(rand() % 100);
    }
}

// Function to print array
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Sequential Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    #pragma omp parallel
    {
        for (int i = 0; i < n - 1; ++i) {
            #pragma omp for
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

// Merge function for Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// Sequential Merge Sort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort helper function
void parallelMergeSortHelper(vector<int>& arr, int l, int r, int depth) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp task if(depth < 4)
        parallelMergeSortHelper(arr, l, m, depth + 1);
        #pragma omp task if(depth < 4)
        parallelMergeSortHelper(arr, m + 1, r, depth + 1);
        #pragma omp taskwait

        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr) {
    #pragma omp parallel
    {
        #pragma omp single
        parallelMergeSortHelper(arr, 0, arr.size() - 1, 0);
    }
}

int main() {
    const int size = 10000; // Size of the array
    vector<int> arr;

    // Generate random array
    generateRandomArray(arr, size);

    // Copy the array for sequential sorting
    vector<int> seqArr = arr;

    // Sequential Bubble Sort
    clock_t startSeqBubble = clock();
    bubbleSort(seqArr);
    clock_t endSeqBubble = clock();
    cout << "Sequential Bubble Sort Time: " << double(endSeqBubble - startSeqBubble) / CLOCKS_PER_SEC << " seconds" << endl;

    // Parallel Bubble Sort
    vector<int> parArr = arr;
    clock_t startParBubble = clock();
    parallelBubbleSort(parArr);
    clock_t endParBubble = clock();
    cout << "Parallel Bubble Sort Time: " << double(endParBubble - startParBubble) / CLOCKS_PER_SEC << " seconds" << endl;

    // Copy the array for sequential sorting
    vector<int> seqArrMerge = arr;

    // Sequential Merge Sort
    clock_t startSeqMerge = clock();
    mergeSort(seqArrMerge, 0, size - 1);
    clock_t endSeqMerge = clock();
    cout << "Sequential Merge Sort Time: " << double(endSeqMerge - startSeqMerge) / CLOCKS_PER_SEC << " seconds" << endl;

    // Parallel Merge Sort
    vector<int> parArrMerge = arr;
    clock_t startParMerge = clock();
    parallelMergeSort(parArrMerge);
    clock_t endParMerge = clock();
    cout << "Parallel Merge Sort Time: " << double(endParMerge - startParMerge) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}
