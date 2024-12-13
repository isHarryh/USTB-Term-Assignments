#pragma once
#include <cmath>
#include <stdexcept>
#include "GeometricObject.h"
using namespace std;

namespace OOP2 {
	class Triangle : public GeometricObject {
	public:
		Triangle();
		Triangle(double, double, double);
		double getSide1() const;
		double getSide2() const;
		double getSide3() const;
		double getArea() const;
		double getPerimeter() const;
	private:
		double side1;
		double side2;
		double side3;
	};
}
