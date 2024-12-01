/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include <iostream>
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "CountSort.h"
using namespace SortingAlgorithm;

number* getRandomArray(int length) {
    number* arr = new number[length];
    for (int i = 0; i < length; i++) {
        arr[i] = 1.0 * rand();
    }
    return arr;
}

int main() {
    const int length = 32768;
    const int seed = 0;
    srand(seed);
    number* arr = getRandomArray(length);

    // Bubble Sort
    {
        cout << "[Bubble Sort]" << endl;
        SortResult result = BubbleSort().apply(arr, length);
        result.display();
    }
    // Selection Sort
    {
        cout << "[Selection Sort]" << endl;
        SortResult result = SelectionSort().apply(arr, length);
        result.display();
    }
    // Insertion Sort
    {
        cout << "[Insertion Sort]" << endl;
        SortResult result = InsertionSort().apply(arr, length);
        result.display();
    }
    // Merge Sort
    {
        cout << "[Merge Sort]" << endl;
        SortResult result = MergeSort().apply(arr, length);
        result.display();
    }
    // Quick Sort
    {
        cout << "[Quick Sort]" << endl;
        SortResult result = QuickSort().apply(arr, length);
        result.display();
    }
    // Count Sort
    {
        cout << "[Count Sort]" << endl;
        SortResult result = CountSort().apply(arr, length);
        result.display();
    }

    return 0;
}
