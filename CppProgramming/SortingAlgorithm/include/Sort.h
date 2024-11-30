/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#pragma once
#include <chrono>
#include <iostream>
#define number double

namespace SortingAlgorithm {
	using namespace std;
	using namespace std::chrono;

	struct SortResult {
	public:
		number* array;
		int length;
		double elapsedTime;

		SortResult() = default;
		void receive(number*, int);
		void display();

	private:
		const int maxDisplay = 50;
		steady_clock::time_point startTime = steady_clock::now();
		steady_clock::time_point endTime;
	};

	class Sort {
	public:
		Sort() = default;
		SortResult apply(number*, int);
		void swap(number*, number*);
		number* copyArray(number*, int);
	};
}
