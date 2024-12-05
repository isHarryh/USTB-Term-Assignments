/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#pragma once

namespace OOP {
	class Rectangle {
	public:
		Rectangle();
		Rectangle(double, double);
		double getWidth();
		double getHeight();
		void setWidth(double);
		void setHeight(double);
		double getArea();
		double getPerimeter();
	private:
		double width;
		double height;
	};
}
