/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "MergeSort.h"

namespace SortingAlgorithm {
	SortResult MergeSort::apply(number* rawArray, int length) {
		SortResult result = SortResult();
		result.receive(partialSort(rawArray, length), length);
		return result;
	}

	number* MergeSort::partialSort(number* array, int length) {
		number* sorted = new number[length];
		if (length > 2) {
			int lLength = length / 2;
			int rLength = length - lLength;
			number* left = partialSort(array, lLength);
			number* right = partialSort(&array[lLength], rLength);

			int i = 0, li = 0, ri = 0;
			while (li < lLength && ri < lLength) {
				sorted[i++] = left[li] < right[ri] ? left[li++] : right[ri++];
			}
			while (li < lLength) {
				sorted[i++] = left[li++];
			}
			while (ri < rLength) {
				sorted[i++] = right[ri++];
			}
		} else if (length == 2) {
			sorted[0] = array[!(array[0] < array[1])];
			sorted[1] = array[array[0] < array[1]];
		}
		else if (length == 1) {
			sorted[0] = array[0];
		}
		return sorted;
	}
}
