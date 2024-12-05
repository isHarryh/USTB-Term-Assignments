/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#pragma once
#include <cmath>

namespace OOP {
	class MyPoint {
	public:
		MyPoint();
		MyPoint(double, double);
		double getX();
		double getY();
		double distance(MyPoint);
	private:
		double x;
		double y;
	};
}
