/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#pragma once
#include "Sort.h"

namespace SortingAlgorithm {
	class MergeSort : public Sort {
	public:
		SortResult apply(number*, int);
	private:
		number* partialSort(number*, int);
	};
}
