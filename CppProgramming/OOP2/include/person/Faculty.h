#pragma once
#include "Employee.h"

namespace OOP2 {
	class Faculty : public Employee {
	public:
		Faculty(const string&, const string&, const string&, const string&, const string&, double, const MyDate&, int, int);
		string toString() const override;
	protected:
		int officeHours;
		int rank;
	};
}
