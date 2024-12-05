/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "EvenNumber.h"

namespace OOP {
	EvenNumber::EvenNumber() {
		this->value = 0;
	}

	EvenNumber::EvenNumber(int value) {
		if (value % 2 == 1)
			throw std::runtime_error("Value should be even");
		this->value = value;
	}

	int EvenNumber::getValue() {
		return value;
	}

	EvenNumber EvenNumber::getNext() {
		return EvenNumber(value + 2);
	}

	EvenNumber EvenNumber::getPrevious() {
		return EvenNumber(value - 2);
	}
}
