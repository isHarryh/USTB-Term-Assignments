#include "person/Employee.h"

namespace OOP2 {
	Employee::Employee(const string& name, const string& address, const string& phone, const string& email, const string& office, double salary, const MyDate& dateHired)
		: Person(name, address, phone, email), office(office), salary(salary), dateHired(dateHired) {
	}

	string Employee::toString() const {
		return "<Employee> " + name;
	}
}
