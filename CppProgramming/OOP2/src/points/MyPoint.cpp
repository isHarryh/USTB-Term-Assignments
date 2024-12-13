#include "points/MyPoint.h"

namespace OOP2 {
	MyPoint::MyPoint()
		: x(0.0), y(0.0) {
	}

	MyPoint::MyPoint(double x, double y)
		: x(x), y(y) {
	}

	double MyPoint::getX() const {
		return x;
	}

	double MyPoint::getY() const {
		return y;
	}

	double MyPoint::distance(const MyPoint& other) const {
		return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
	}
}
