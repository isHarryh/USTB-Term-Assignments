#pragma once
#include <string>
using namespace std;

namespace OOP2 {
	class Person {
	public:
		Person(const string&, const string&, const string&, const string&);
		virtual string toString() const;
	protected:
		string name;
		string address;
		string phone;
		string email;
	};
}
