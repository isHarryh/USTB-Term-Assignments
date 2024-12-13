#include "points/ThreeDPoint.h"

namespace OOP2 {
	ThreeDPoint::ThreeDPoint()
		: MyPoint(), z(0.0) {
	}

	ThreeDPoint::ThreeDPoint(double x, double y, double z)
		: MyPoint(x, y), z(z) {
	}

	double ThreeDPoint::getZ() const {
		return z;
	}

	double ThreeDPoint::distance(const ThreeDPoint& other) const {
		return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
	}
}
