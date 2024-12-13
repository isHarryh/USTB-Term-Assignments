#include <iostream>
#include <string>
#include "geometric/Triangle.h"
#include "person/Person.h"
#include "person/Student.h"
#include "person/Employee.h"
#include "person/Faculty.h"
#include "person/Staff.h"
#include "person/MyDate.h"
#include "points/ThreeDPoint.h"
using namespace std;
using namespace OOP2;

int main() {
	double s1, s2, s3;
	string col;
	int fil;
	cin >> s1 >> s2 >> s3 >> col >> fil;
	Triangle* tri = new Triangle(s1, s2, s3);
	tri->setColor(col);
	tri->setFilled(fil);
	cout << "Triangle Area=" << tri->getArea() << " Perimeter=" << tri->getPerimeter()
		<< " Color=" << tri->getColor() << " Filled=" << tri->isFilled() << endl;
	cout << endl;

	Person* p1 = new Person("Peter", "101 Rd", "123456", "peter@test.com");
	Person* p2 = new Student("Bob", "102 Rd", "234561", "bob@test.com", "freshman");
	Person* p3 = new Employee("Alice", "103 Rd", "345612", "alice@test.com", "Test Co.Ltd", 7000.0, MyDate(2024, 9, 1));
	Person* p4 = new Faculty("Joe", "104 Rd", "456123", "joe@test.com", "Test Co.Ltd", 8000.0, MyDate(2023, 9, 1), 40, 1);
	Person* p5 = new Staff("Harry", "105 Rd", "561234", "harry@test.com", "Test Co.Ltd", 9000.0, MyDate(2022, 9, 1), "Manager");
	cout << p1->toString() << endl;
	cout << p2->toString() << endl;
	cout << p3->toString() << endl;
	cout << p4->toString() << endl;
	cout << p5->toString() << endl;
	cout << endl;

	ThreeDPoint* a = new ThreeDPoint();
	ThreeDPoint* b = new ThreeDPoint(10.0, 30.0, 25.5);
	cout << "Distance between two points: " << a->distance(*b) << endl;
	cout << endl;

	return 0;
}
