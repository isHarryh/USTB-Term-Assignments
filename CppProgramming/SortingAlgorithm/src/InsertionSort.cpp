/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "InsertionSort.h"

namespace SortingAlgorithm {
	SortResult InsertionSort::apply(number* rawArray, int length) {
		number* array = copyArray(rawArray, length);
		SortResult result = SortResult();

		for (int i = 1; i < length; i++) {
			for (int k = i, j = i - 1; j >= 0; j--) {
				if (array[k] < array[j]) {
					swap(&array[k], &array[j]);
					k = j;
				}
			}
		}

		result.receive(array, length);
		return result;
	}
}
