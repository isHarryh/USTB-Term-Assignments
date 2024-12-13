#pragma once
#include <string>
using namespace std;

namespace OOP2 {
	class GeometricObject {
	public:
		GeometricObject();
		GeometricObject(const string& color, bool filled);
		string getColor() const;
		void setColor(const string& color);
		bool isFilled() const;
		void setFilled(bool filled);
		string toString() const;
	private:
		string color;
		bool filled;
	};
}
