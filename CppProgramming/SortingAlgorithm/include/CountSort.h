/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#pragma once
#include "Sort.h"
#include <map>

namespace SortingAlgorithm {
	class CountSort : public Sort {
	public:
		SortResult apply(number*, int);
	private:
		map<number, int> getCounts(number*, int);
		number* recover(map<number, int>, int);
	};
}
