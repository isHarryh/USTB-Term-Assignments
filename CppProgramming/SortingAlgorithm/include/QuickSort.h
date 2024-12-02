/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#pragma once
#include "Sort.h"

namespace SortingAlgorithm {
	class QuickSort : public Sort {
	public:
		SortResult apply(number*, int);
	private:
		void partialSort(number*, int);
		int getPivot(number*, int);
	};
}
