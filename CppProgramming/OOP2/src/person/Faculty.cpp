#include "person/Faculty.h"

namespace OOP2 {
	Faculty::Faculty(const string& name, const string& address, const string& phone, const string& email, const string& office, double salary, const MyDate& dateHired, int officeHours, int rank)
		: Employee(name, address, phone, email, office, salary, dateHired), officeHours(officeHours), rank(rank) {
	}

	string Faculty::toString() const {
		return "<Faculty> " + name;
	}
}
