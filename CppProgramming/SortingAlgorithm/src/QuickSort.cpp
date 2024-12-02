/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "QuickSort.h"

namespace SortingAlgorithm {
	SortResult QuickSort::apply(number* rawArray, int length) {
		SortResult result = SortResult();
		number* sorted = copyArray(rawArray, length);
		partialSort(sorted, length);
		result.receive(sorted, length);
		return result;
	}

	void QuickSort::partialSort(number* array, int length) {
		if (length > 1) {
			int pivotIdx = getPivot(array, length);
			partialSort(array, pivotIdx);
			partialSort(&array[pivotIdx + 1], length - pivotIdx - 1);
		}
	}

	int QuickSort::getPivot(number* array, int length) {
		int pivotIdx = 0;
		int storeIdx = pivotIdx;
		for (int i = pivotIdx + 1; i < length; i++) {
			if (array[i] < array[pivotIdx] || (array[i] == array[pivotIdx] && rand() % 2)) {
				swap(&array[i], &array[++storeIdx]);
			}
		}
		swap(&array[pivotIdx], &array[storeIdx]);
		return storeIdx;
	}
}
