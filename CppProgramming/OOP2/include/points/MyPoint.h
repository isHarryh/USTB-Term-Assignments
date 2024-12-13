#pragma once
#include <cmath>

namespace OOP2 {
	class MyPoint {
	public:
		MyPoint();
		MyPoint(double, double);
		double getX() const;
		double getY() const;
		double distance(const MyPoint&) const;
	protected:
		double x;
		double y;
	};
}
