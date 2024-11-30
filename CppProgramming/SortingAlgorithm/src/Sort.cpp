/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "Sort.h"

namespace SortingAlgorithm {
	void SortResult::receive(number* array, int length) {
		this->array = array;
		this->length = length;

		endTime = steady_clock::now();
		elapsedTime = duration_cast<microseconds>(endTime - startTime).count() / 1000000.0;
	}

	void SortResult::display() {
		cout << "Result: " << "Sorted " << length << " items in " << elapsedTime << "s." << endl;
		cout << "Preview: ";
		if (length > maxDisplay) {
			for (int i = 0; i < maxDisplay / 2; i++) {
				cout << array[i] << " ";
			}
			cout << "... ";
			for (int i = length - maxDisplay / 2; i < length; i++) {
				cout << array[i] << " ";
			}
			cout << endl;
		}
		else {
			for (int i = 0; i < length; i++) {
				cout << array[i] << " ";
			}
			cout << endl;
		}
	}

	void Sort::swap(number* a, number* b) {
		number t = *a;
		*a = *b;
		*b = t;
	}

	number* Sort::copyArray(number* rawArray, int length) {
		number* array = new number[length];
		memcpy(array, rawArray, sizeof(number) * length);
		return array;
	}
}
