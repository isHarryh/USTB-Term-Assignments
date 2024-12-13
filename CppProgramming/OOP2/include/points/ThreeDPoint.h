#pragma once
#include "MyPoint.h"

namespace OOP2 {
	class ThreeDPoint : public MyPoint {
	public:
		ThreeDPoint();
		ThreeDPoint(double, double, double);
		double getZ() const;
		double distance(const ThreeDPoint&) const;
	protected:
		double z;
	};
}
