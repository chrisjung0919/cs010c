#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

static const int ARRAY_SIZE = 50000; // Number of elements in each array
static const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000; // Used to convert clock ticks to milliseconds

// Generate a random integer between low and high (inclusive)
static int GenerateRandomInteger(int lowerBound, int upperBound) {
    return lowerBound + rand() % (upperBound - lowerBound + 1);
}

// Fill three arrays with the same set of random integers
static void InitializeArrays(int randomArray1[], int randomArray2[], int randomArray3[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        randomArray1[i] = GenerateRandomInteger(0, ARRAY_SIZE);
        randomArray2[i] = randomArray1[i];
        randomArray3[i] = randomArray1[i];
    }
}

// Partition the array around a pivot value
static int PartitionArray(int arr[], int leftIndex, int rightIndex, int pivotValue) {
    while (true) {

        // Move the left index to the right as long as elements are less than the pivot
        while (arr[leftIndex] < pivotValue) {
            leftIndex++;
        }

        // Move the right index to the left as long as elements are greater than the pivot
        while (arr[rightIndex] > pivotValue) {
            rightIndex--;
        }

        if (leftIndex >= rightIndex) {
            return rightIndex;
        } else {
            // Swap the elements at leftIndex and rightIndex to move them into the correct partition
            int swapValue = arr[leftIndex];
            arr[leftIndex] = arr[rightIndex];
            arr[rightIndex] = swapValue;

            leftIndex++;
            rightIndex--;
        }
    }

    return rightIndex;
}

// Quicksort using the middle element as the pivot
static void Quicksort_midpoint(int arr[], int leftIndex, int rightIndex) {
    if (leftIndex >= rightIndex) {
        return;
    }

    // Choose the middle element as the pivot
    int pivotValue = arr[(leftIndex + rightIndex) / 2];

    int partitionIndex = PartitionArray(arr, leftIndex, rightIndex, pivotValue);

    // Recursively apply quicksort to the left and right subarrays
    Quicksort_midpoint(arr, leftIndex, partitionIndex);
    Quicksort_midpoint(arr, partitionIndex + 1, rightIndex);
}

// Quicksort using the median of the first, middle, and last elements as the pivot
static void Quicksort_medianOfThree(int arr[], int leftIndex, int rightIndex) {
    if (leftIndex >= rightIndex) {
        return;
    }

    // Calculate the index of the middle element
    int middleIndex = (leftIndex + rightIndex) / 2;

    // Choose the pivot as the median of the first, middle, and last elements
    int pivotValue = max(min(arr[leftIndex], arr[middleIndex]), min(max(arr[leftIndex], arr[middleIndex]), arr[rightIndex]));

    int partitionIndex = PartitionArray(arr, leftIndex, rightIndex, pivotValue);

    // Recursively apply quicksort to the left and right subarrays
    Quicksort_medianOfThree(arr, leftIndex, partitionIndex);
    Quicksort_medianOfThree(arr, partitionIndex + 1, rightIndex);
}

// Insertion sort implementation
static void InsertionSort(int arr[], int arrSize) {
    int swapValue;
    int currentIndex;

    // Start from the second element and move forward
    for (int i = 1; i < arrSize; i++) {
        currentIndex = i;

        while (currentIndex > 0 && arr[currentIndex] < arr[currentIndex - 1]) {
            // Swap the current element with the one before it
            swapValue = arr[currentIndex];
            arr[currentIndex] = arr[currentIndex - 1];
            arr[currentIndex - 1] = swapValue;
            currentIndex--;
        }
    }
}

// Check if an array is sorted in non-decreasing order
static bool IsArraySorted(int arr[], int arrSize) {
    // Array size is zero which means the array is empty
    if (arrSize <= 0) {
        return true;
    }

    int previousValue = arr[0];

    // travel through the array
    for (int i = 0; i < arrSize; i++) {
        int currentValue = arr[i];

        // If a current element is less than the previous one, the array is not sorted
        if (currentValue < previousValue) {
            return false;
        }

        previousValue = currentValue;
    }

    // True means the array is sorted
    return true;
}

int main() {
    // Declare arrays to be sorted by different algorithms
    int arrayForQuickMidpoint[ARRAY_SIZE];
    int arrayForQuickMedian[ARRAY_SIZE];
    int arrayForInsertionSort[ARRAY_SIZE];

    // Fill all arrays with the same random data
    InitializeArrays(arrayForQuickMidpoint, arrayForQuickMedian, arrayForInsertionSort);

    // Time quicksort with midpoint pivot
    clock_t startTime = clock();
    Quicksort_midpoint(arrayForQuickMidpoint, 0, ARRAY_SIZE - 1);
    clock_t endTime = clock();
    int duration = (endTime - startTime) / CLOCKS_PER_MS;
    cout << "Quick sort midpoint took " << duration << " seconds." << endl;
    cout << "Quick sort midpoint is " << (IsArraySorted(arrayForQuickMidpoint, ARRAY_SIZE) ? "GOOD" : "BAD") << endl;

    // Time quicksort with median-of-three pivot
    startTime = clock();
    Quicksort_medianOfThree(arrayForQuickMedian, 0, ARRAY_SIZE - 1);
    endTime = clock();
    duration = (endTime - startTime) / CLOCKS_PER_MS;
    cout << "Quick sort median took " << duration << " seconds." << endl;
    cout << "Quick sort median is " << (IsArraySorted(arrayForQuickMedian, ARRAY_SIZE) ? "GOOD" : "BAD") << endl;

    // Time insertion sort
    startTime = clock();
    InsertionSort(arrayForInsertionSort, ARRAY_SIZE);
    endTime = clock();
    duration = (endTime - startTime) / CLOCKS_PER_MS;
    cout << "Insertion sort took " << duration << " seconds." << endl;
    cout << "Insertion sort is " << (IsArraySorted(arrayForInsertionSort, ARRAY_SIZE) ? "GOOD" : "BAD") << endl;

    return 0;
}
