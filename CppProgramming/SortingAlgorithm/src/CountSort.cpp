/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "CountSort.h"

namespace SortingAlgorithm {
	SortResult CountSort::apply(number* rawArray, int length) {
		SortResult result = SortResult();
		result.receive(recover(getCounts(rawArray, length), length), length);
		return result;
	}

	map<number, int> CountSort::getCounts(number* rawArray, int length) {
		map<number, int> counts = map<number, int>();
		for (int i = 0; i < length; i++) {
			if (counts.find(rawArray[i]) == counts.end()) {
				counts[rawArray[i]] = 1;
			}
			else {
				counts[rawArray[i]] += 1;
			}
		}
		return counts;
	}

	number* CountSort::recover(map<number, int> counts, int length) {
		number* sorted = new number[length];
		int i = 0;
		for (map<number, int>::iterator iter = counts.begin(); iter != counts.end() && i < length; iter++) {
			for (int j = 0; j < iter->second && i < length; j++) {
				sorted[i++] = iter->first;
			}
		}
		return sorted;
	}
}
