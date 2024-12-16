#pragma once
#include "GameObject.h"

namespace RaylibTest {
	class Train : public GameObject {
	public:
		Train();
		Train(Color color);
		void draw() override;
	protected:
		Color mainColor;
	};
}
