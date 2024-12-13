# Object Oriented Programming Assignment 2

## 1. The Triangle Class

### Question

Design a class named **Triangle** that extends **GeometricObject**. The class contains the following:

1. Three double data fields named `side1`, `side2`, and `side3` to denote three sides of the triangle.
2. A no-arg constructor that creates a default triangle with each side `1.0`.
3. A constructor that creates a rectangle with the specified `side1`, `side2`, and `side3`.
4. The constant accessor functions for all three data fields.
5. A constant function named `getArea()` that returns the area of this triangle.
6. A constant function named `getPerimeter()` that returns the perimeter of this triangle.

Implement the class. Write a test program that prompts the user to enter three sides of the triangle, enter a color, and enter `1` or `0` to indicate whether the triangle is filled. The program should create a Triangle object with these sides and set the color and filled properties using the input. The program should display the area, perimeter, color, and `true` or `false` to indicate whether filled or not.

The class GeometricObject is defined as follows:

```cpp
class GeometricObject
{
public:
	GeometricObject();
	GeometricObject(const string& color, bool filled);
	string getColor() const;
	void setColor(const string& color);
	bool isFilled() const;
	void setFilled(bool filled);
	string toString() const;
private:
	string color;
	bool filled;
};
GeometricObject::GeometricObject()
{
	color = "white";
	filled = false;
}
GeometricObject::GeometricObject(const string& color, bool filled)
{
	this->color = color;
	this->filled = filled;
}
string GeometricObject::getColor() const
{
	return color;
}
void GeometricObject::setColor(const string& color)
{
	this->color = color;
}
bool GeometricObject::isFilled() const
{
	return filled;
}
void GeometricObject::setFilled(bool filled)
{
	this->filled = filled;
}
string GeometricObject::toString() const
{
	return "Geometric Object";
}
```

### Code

Triangle class declaration:

```cpp
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
```

Triangle class implementation:

```cpp
Triangle::Triangle() {
	this->side1 = 1.0;
	this->side2 = 1.0;
	this->side3 = 1.0;
}

Triangle::Triangle(double side1, double side2, double side3) {
	if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1)
		throw runtime_error("Invalid arguments");
	this->side1 = side1;
	this->side2 = side2;
	this->side3 = side3;
}

double Triangle::getSide1() const {
	return side1;
}

double Triangle::getSide2() const {
	return side2;
}

double Triangle::getSide3() const {
	return side3;
}

double Triangle::getArea() const {
	double s = (side1 + side2 + side3) / 2;
	return sqrt(s * (s - side1) * (s - side2) * (s - side3));
}

double Triangle::getPerimeter() const {
	return side1 + side2 + side3;
}
```

Triangle test:

```cpp
double s1, s2, s3;
string col;
int fil;
cin >> s1 >> s2 >> s3 >> col >> fil;
Triangle* tri = new Triangle(s1, s2, s3);
tri->setColor(col);
tri->setFilled(fil);
cout << "Triangle Area=" << tri->getArea() << " Perimeter=" << tri->getPerimeter()
    << " Color=" << tri->getColor() << " Filled=" << tri->isFilled() << endl;
```

### Result

```cpp
4 5 6 blue 1
Triangle Area=9.92157 Perimeter=15 Color=blue Filled=1
```

<div style="page-break-after:always"></div>

---

## 2. The Person, Student, Employee, Faculty, and Staff Classes

### Question

Design a class named **Person** and its two derived classes named **Student** and **Employee**.

Make **Faculty** and **Staff** derived classes of Employee. A person has a name, address, phone number, and e-mail address. A student has a class status (freshman, sophomore, junior, or senior). An employee has an office, salary, and date-hired. Define a class named **MyDate** that contains the fields year, month, and day. A faculty member has office hours and a rank. A staff member has a title.

Define a constant virtual `toString()` function in the Person class and override it in each class to display the class name and the person’s name.
Implement the classes. Write a test program that creates a Person, Student, Employee, Faculty, and Staff, and invokes their `toString()` functions.

### Code

Declarations:

```cpp
class Person {
public:
    Person(const string&, const string&, const string&, const string&);
    virtual string toString() const;
protected:
    string name;
    string address;
    string phone;
    string email;
};
    
class Student : public Person {
public:
    Student(const string&, const string&, const string&, const string&, const string&);
    string toString() const override;
protected:
    string status;
};

class Employee : public Person {
public:
    Employee(const string&, const string&, const string&, const string&, const string&, double, const MyDate&);
    virtual string toString() const override;
protected:
    string office;
    double salary;
    MyDate dateHired;
};

class Faculty : public Employee {
public:
    Faculty(const string&, const string&, const string&, const string&, const string&, double, const MyDate&, int, int);
    string toString() const override;
protected:
    int officeHours;
    int rank;
};

class Staff : public Employee {
public:
    Staff(const string&, const string&, const string&, const string&, const string&, double, const MyDate&, const string&);
    string toString() const override;
protected:
    string title;
};

class MyDate {
public:
    int year;
    int month;
    int day;
    MyDate(int, int, int);
};
```

Implementations:

```cpp
Person::Person(const string& name, const string& address, const string& phone, const string& email)
    : name(name), address(address), phone(phone), email(email) {
}

string Person::toString() const {
    return "<Person> " + name;
}

Student::Student(const string& name, const string& address, const string& phone, const string& email, const string& status)
    : Person(name, address, phone, email), status(status) {
}

string Student::toString() const {
    return "<Student> " + name;
}

Employee::Employee(const string& name, const string& address, const string& phone, const string& email, const string& office, double salary, const MyDate& dateHired)
    : Person(name, address, phone, email), office(office), salary(salary), dateHired(dateHired) {
}

string Employee::toString() const {
    return "<Employee> " + name;
}

Faculty::Faculty(const string& name, const string& address, const string& phone, const string& email, const string& office, double salary, const MyDate& dateHired, int officeHours, int rank)
    : Employee(name, address, phone, email, office, salary, dateHired), officeHours(officeHours), rank(rank) {
}

string Faculty::toString() const {
    return "<Faculty> " + name;
}

Staff::Staff(const string& name, const string& address, const string& phone, const string& email, const string& office, double salary, const MyDate& dateHired, const string& title)
    : Employee(name, address, phone, email, office, salary, dateHired), title(title) {
}

string Staff::toString() const {
    return "<Staff> " + name;
}

MyDate::MyDate(int year, int month, int day)
    : year(year), month(month), day(day) {
}
```

Test:

```cpp
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
```

### Result

```cpp
<Person> Peter
<Student> Bob
<Employee> Alice
<Faculty> Joe
<Staff> Harry
```

<div style="page-break-after:always"></div>

---

## 3. The 3D Point Class

### Question

Design a class named **MyPoint** to represent a point with x and y-coordinates. The class contains:

1. Two data fields x and y that represent the coordinates.
2. A no-arg constructor that creates a point `(0, 0)`.
3. A constructor that constructs a point with specified coordinates.
4. Two get functions for data fields x and y, respectively.
5. A function named distance that returns the distance from this point to another point of the MyPoint type.

Design a class named **ThreeDPoint** to model a point in a three-dimensional space. Let ThreeDPoint be derived from MyPoint with the following additional features:

1. A data field named z that represents the z-coordinate.
2. A no-arg constructor that constructs a point with coordinates `(0, 0, 0)`.
3. A constructor that constructs a point with three specified coordinates.
4. A constant get function that returns the z value.
5. A constant `distance(const MyPoint&)` function to return the distance between this point and the other point in the three-dimensional space.

Implement the classes. Write a test program that creates two points `(0, 0, 0)` and `(10, 30, 25.5)` and displays the distance between them.

### Code

Declarations:

```cpp
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


class ThreeDPoint : public MyPoint {
public:
	ThreeDPoint();
	ThreeDPoint(double, double, double);
	double getZ() const;
	double distance(const ThreeDPoint&) const;
protected:
	double z;
};
```

Implementations:

```cpp
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
```

Test:

```cpp
ThreeDPoint* a = new ThreeDPoint();
ThreeDPoint* b = new ThreeDPoint(10.0, 30.0, 25.5);
cout << "Distance between two points: " << a->distance(*b) << endl;
```

### Result

```
Distance between two points: 40.6233
```

---

> The above code source are opened on GitHub: https://github.com/isHarryh/USTB-Term-Assignments/tree/main/CppProgramming/OOP2
