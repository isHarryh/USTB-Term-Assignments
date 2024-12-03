/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "RadixSort.h"
#include <vector>

namespace SortingAlgorithm {
	SortResult RadixSort::apply(number* rawArray, int length) {
		SortResult result = SortResult();

		number* array = copyArray(rawArray, length);
		vector<vector<number>> buckets = vector<vector<number>>(19);
		int exp = 0;
		while (buckets[9].size() < length) {
			for (int b = 0; b < 19; b++) {
				buckets[b].clear();
			}

			long long div = 1;
			for (int e = 0; e < exp; e++) {
				div *= 10;
			}

			for (int i = 0; i < length; i++) {
				buckets[(long long)array[i] / div % 10 + 9].push_back(array[i]);
			}

			int i = 0;
			for (int b = 0; b < 19; b++) {
				for (int k = 0; k < buckets[b].size(); k++) {
					array[i++] = buckets[b][k];
				}
			}

			exp++;
		}

		result.receive(array, length);
		return result;
	}
}
