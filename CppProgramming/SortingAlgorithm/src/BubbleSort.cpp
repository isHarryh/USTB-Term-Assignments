/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "BubbleSort.h"

namespace SortingAlgorithm {
	SortResult BubbleSort::apply(number* rawArray, int length) {
		number* array = copyArray(rawArray, length);
		SortResult result = SortResult();

		for (int i = 0; i < length - 1; i++) {
			bool sorted = true;
			for (int j = 0; j < length - i - 1; j++) {
				if (array[j] > array[j + 1]) {
					swap(&array[j], &array[j + 1]);
					sorted = false;
				}
			}
			if (sorted) {
				break;
			}
		}

		result.receive(array, length);
		return result;
	}
}
