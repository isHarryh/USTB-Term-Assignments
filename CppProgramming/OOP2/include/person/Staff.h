#pragma once
#include "Employee.h"
using namespace std;

namespace OOP2 {
	class Staff : public Employee {
	public:
		Staff(const string&, const string&, const string&, const string&, const string&, double, const MyDate&, const string&);
		string toString() const override;
	protected:
		string title;
	};
}
