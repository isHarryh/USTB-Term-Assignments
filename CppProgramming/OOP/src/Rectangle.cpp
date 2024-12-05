/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include "Rectangle.h"

namespace OOP {
	Rectangle::Rectangle() {
		this->width = 1.0;
		this->height = 1.0;
	}

	Rectangle::Rectangle(double width, double height) {
		this->width = width;
		this->height = height;
	}

	double Rectangle::getWidth() {
		return width;
	}

	double Rectangle::getHeight() {
		return height;
	}

	void Rectangle::setWidth(double width) {
		this->width = width;
	}

	void Rectangle::setHeight(double height) {
		this->height = height;
	}

	double Rectangle::getArea() {
		return width * height;
	}

	double Rectangle::getPerimeter() {
		return (width + height) * 2;
	}
}
