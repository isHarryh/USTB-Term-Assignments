# Object Oriented Programming Assignment

## 1. The Time Class

### Question

Design a class named Time. The class contains:

1. Data fields hour, minute, and second that represent a time.
2. A no-arg constructor that creates a Time object for the current time.
3. A constructor that constructs a Time object with a specified elapse time since the middle of night, Jan 1, 1970, in seconds.
4. A constructor that constructs a Time object with the specified hour, minute, and
second.
5. Three get functions for the data fields hour, minute, and second.
6. A function named `setTime(int elapseTime)` that sets a new time for the object using the elapsed time.

Implement the class. Write a test program that creates two Time objects, one using a no-arg constructor and the other using `Time(555550)`, and display their hour, minute, and second.

> Hint: The first two constructors will extract hour, minute, and second from the elapse time. For example, if the elapse time is 555550 seconds, the hour is 10, the minute is 19, and the second is 9. For the no-arg constructor, the current time can be obtained using `time(0)`.

### Code

MyTime class declaration:

```cpp
class MyTime {
public:
    MyTime();
    MyTime(long long);
    MyTime(int, int, int);
    int getHour();
    int getMinute();
    int getSecond();
    void setTime(long long);
private:
    int hour;
    int minute;
    int second;
};
```

MyTime class implementation:

```cpp
MyTime::MyTime() {
    setTime(std::time(0));
}

MyTime::MyTime(long long elapseTime) {
    setTime(elapseTime);
}

MyTime::MyTime(int hour, int minute, int second) {
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

int MyTime::getHour() {
    return hour;
}

int MyTime::getMinute() {
    return minute;
}

int MyTime::getSecond() {
    return second;
}

void MyTime::setTime(long long elapseTime) {
    elapseTime--;
    this->hour = elapseTime / 3600 % 24;
    this->minute = elapseTime / 60 % 60;
    this->second = elapseTime % 60;
}
```

MyTime test:

```cpp
MyTime t1 = MyTime();
MyTime t2 = MyTime(555550);
cout << "Current time: " << t1.getHour() << "h " << t1.getMinute() << "min " << t1.getSecond() << "s" << endl;
cout << "Other time: " << t2.getHour() << "h " << t2.getMinute() << "min " << t2.getSecond() << "s" << endl;
```

### Result

```cpp
Current time: 3h 22min 11s
Other time: 10h 19min 10s
```

-----

## 2. The EvenNumber class

### Question

Define the EvenNumber class for representing an even number. The class contains:

1. A data field value of the int type that represents the integer value stored in the object.
2. A no-arg constructor that creates an EvenNumber object for the value 0.
3. A constructor that constructs an EvenNumber object with the specified value.
4. A function named `getValue()` to return an int value for this object.
5. A function named `getNext()` to return an EvenNumber object that represents the next even number after the current even number in this object.
6. A function named `getPrevious()` to return an EvenNumber object that represents the previous even number before the current even number in this object.

Implement the class. Write a test program that creates an EvenNumber object for value 16 and invokes the `getNext()` and `getPrevious()` functions to obtain and displays these numbers.

### Code

EvenNumber declaration:

```cpp
class EvenNumber {
public:
    EvenNumber();
    EvenNumber(int);
    int getValue();
    EvenNumber getNext();
    EvenNumber getPrevious();
private:
    int value;
};
```

EvenNumber implementation:

```cpp
EvenNumber::EvenNumber() {
    this->value = 0;
}

EvenNumber::EvenNumber(int value) {
    if (value % 2 == 1)
        throw std::runtime_error("Value should be even");
    this->value = value;
}

int EvenNumber::getValue() {
    return value;
}

EvenNumber EvenNumber::getNext() {
    return EvenNumber(value + 2);
}

EvenNumber EvenNumber::getPrevious() {
    return EvenNumber(value - 2);
}
```

EvenNumber test:

```cpp
EvenNumber en = EvenNumber(16);
cout << "Next even number: " << en.getNext().getValue() << endl;
cout << "Previous even number: " << en.getPrevious().getValue() << endl;
```

### Result

```cpp
Next even number: 18
Previous even number: 14
```

-----

## 3. The MyPoint class

### Question

Design a class named MyPoint to represent a point with x and y-coordinates. The class contains:

1. Two data fields x and y that represent the coordinates.
2. A no-arg constructor that creates a point $(0, 0)$.
3. A constructor that constructs a point with specified coordinates.
4. Two get functions for data fields x and y, respectively.
5. A function named `distance` that returns the distance from this point to another point of the MyPoint type.

Implement the class. Write a test program that creates two points $(0, 0)$ and $(10, 30.5)$ and displays the distance between them.

### Code

MyPoint declaration:

```cpp
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
```

MyPoint implementation:

```cpp
MyPoint::MyPoint() {
    this->x = 0.0;
    this->y = 0.0;
}

MyPoint::MyPoint(double x, double y) {
    this->x = x;
    this->y = y;
}

double MyPoint::getX() {
    return x;
}

double MyPoint::getY() {
    return y;
}

double MyPoint::distance(MyPoint other) {
    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}
```

MyPoint test:

```cpp
MyPoint p1 = MyPoint();
MyPoint p2 = MyPoint(10.0, 30.5);
cout << "Distance between two points: " << p1.distance(p2) << endl;
```

### Result

```cpp
Distance between two points: 32.0975
```

-----

## 4. The Rectangle class

### Question

Design a class named Rectangle to represent a rectangle.
The class contains:

1. Two double data fields named width and height that specify the width and
height of the rectangle.
2. A no-arg constructor that creates a rectangle with width 1 and height 1.
3. A constructor that creates a default rectangle with the specified width and
height.
4. The accessor and mutator functions for all the data fields.
5. A function named `getArea()` that returns the area of this rectangle.
6. A function named `getPerimeter()` that returns the perimeter.

Implement the class. Write a test program that creates two Rectangle objects. Assign width 4 and height 40 to the first object and width 3.5 and height 35.9 to the second. Display the properties of both objects and find their areas and perimeters.

### Code

Rectangle declaration:

```cpp
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
```

Rectangle implementation:

```cpp
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
```

Rectangle test:

```cpp
Rectangle r1 = Rectangle(4.0, 40.0);
Rectangle r2 = Rectangle(3.5, 35.9);
cout << "Rectangle A: " << r1.getWidth() << "*" << r1.getHeight() << " area=" << r1.getArea() << " perimeter=" << r1.getPerimeter() << endl;
cout << "Rectangle B: " << r2.getWidth() << "*" << r2.getHeight() << " area=" << r2.getArea() << " perimeter=" << r2.getPerimeter() << endl;
```

### Result

```cpp
Rectangle A: 4*40 area=160 perimeter=88
Rectangle B: 3.5*35.9 area=125.65 perimeter=78.8
```

---

> The above code source are opened on GitHub: https://github.com/isHarryh/USTB-Term-Assignments/tree/main/CppProgramming/OOP
