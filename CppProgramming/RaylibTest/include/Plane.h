#pragma once
#include "GameObject.h"

namespace RaylibTest {
	class Plane : public GameObject {
	public:
		Plane();
		Plane(Color color);
		void draw() override;
	protected:
		Color mainColor;
	};
}
