#include "person/Student.h"

namespace OOP2 {
	Student::Student(const string& name, const string& address, const string& phone, const string& email, const string& status)
		: Person(name, address, phone, email), status(status) {
	}

	string Student::toString() const {
		return "<Student> " + name;
	}
}
