/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#pragma once
#include <stdexcept>

namespace OOP {
	class EvenNumber {
	public:
		EvenNumber();
		EvenNumber(int);
		int getValue();
		EvenNumber getNext();
		EvenNumber getPrevious();
	private:
		int value;
	};
}
