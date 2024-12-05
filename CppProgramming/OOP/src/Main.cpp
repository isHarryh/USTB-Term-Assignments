/**
 * Copyright (c) 2024, Harry Huang
 * @ MIT License
 */
#include <iostream>
#include "MyTime.h"
#include "EvenNumber.h"
#include "MyPoint.h"
#include "Rectangle.h"
using namespace std;
using namespace OOP;

int main() {
	MyTime t1 = MyTime();
	MyTime t2 = MyTime(555550);
	cout << "Current time: " << t1.getHour() << "h " << t1.getMinute() << "min " << t1.getSecond() << "s" << endl;
	cout << "Other time: " << t2.getHour() << "h " << t2.getMinute() << "min " << t2.getSecond() << "s" << endl;
	cout << endl;

	EvenNumber en = EvenNumber(16);
	cout << "Next even number: " << en.getNext().getValue() << endl;
	cout << "Previous even number: " << en.getPrevious().getValue() << endl;
	cout << endl;

	MyPoint p1 = MyPoint();
	MyPoint p2 = MyPoint(10.0, 30.5);
	cout << "Distance between two points: " << p1.distance(p2) << endl;
	cout << endl;

	Rectangle r1 = Rectangle(4.0, 40.0);
	Rectangle r2 = Rectangle(3.5, 35.9);
	cout << "Rectangle A: " << r1.getWidth() << "*" << r1.getHeight() << " area=" << r1.getArea() << " perimeter=" << r1.getPerimeter() << endl;
	cout << "Rectangle B: " << r2.getWidth() << "*" << r2.getHeight() << " area=" << r2.getArea() << " perimeter=" << r2.getPerimeter() << endl;
	cout << endl;
	return 0;
}
