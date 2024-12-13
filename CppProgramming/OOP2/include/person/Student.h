#pragma once
#include "Person.h"

namespace OOP2 {
	class Student : public Person {
	public:
		Student(const string&, const string&, const string&, const string&, const string&);
		string toString() const override;
	protected:
		string status;
	};
}
