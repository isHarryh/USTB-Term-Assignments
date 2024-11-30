/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "SelectionSort.h"

namespace SortingAlgorithm {
	SortResult SelectionSort::apply(number* rawArray, int length) {
		number* array = copyArray(rawArray, length);
		SortResult result = SortResult();

		for (int i = 0; i < length - 1; i++) {
			number* min = &array[i];
			for (int j = i + 1; j < length; j++) {
				if (array[j] < *min) {
					min = &array[j];
				}
			}
			swap(min, &array[i]);
		}

		result.receive(array, length);
		return result;
	}
}
