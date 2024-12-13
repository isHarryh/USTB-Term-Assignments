#include "person/Person.h"

namespace OOP2 {
	Person::Person(const string& name, const string& address, const string& phone, const string& email)
		: name(name), address(address), phone(phone), email(email) {
	}

	string Person::toString() const {
		return "<Person> " + name;
	}
}
