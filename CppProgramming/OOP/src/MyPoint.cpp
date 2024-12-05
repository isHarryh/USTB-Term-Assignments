/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "MyPoint.h"

namespace OOP {
	MyPoint::MyPoint() {
		this->x = 0.0;
		this->y = 0.0;
	}

	MyPoint::MyPoint(double x, double y) {
		this->x = x;
		this->y = y;
	}

	double MyPoint::getX() {
		return x;
	}

	double MyPoint::getY() {
		return y;
	}

	double MyPoint::distance(MyPoint other) {
		return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
	}
}
