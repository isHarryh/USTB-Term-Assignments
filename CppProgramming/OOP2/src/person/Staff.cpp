#include "person/Staff.h"

namespace OOP2 {
	Staff::Staff(const string& name, const string& address, const string& phone, const string& email, const string& office, double salary, const MyDate& dateHired, const string& title)
		: Employee(name, address, phone, email, office, salary, dateHired), title(title) {
	}

	string Staff::toString() const {
		return "<Staff> " + name;
	}
}
