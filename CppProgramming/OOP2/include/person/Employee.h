#pragma once
#include "Person.h"
#include "MyDate.h"

namespace OOP2 {
	class Employee : public Person {
	public:
		Employee(const string&, const string&, const string&, const string&, const string&, double, const MyDate&);
		virtual string toString() const override;
	protected:
		string office;
		double salary;
		MyDate dateHired;
	};
}
