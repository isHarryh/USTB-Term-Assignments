#pragma once
#include <math.h>
#include "raylib.h"

namespace RaylibTest {
	class GameObject {
	public:
		GameObject();
		// Draws the object to the screen.
		virtual void draw();
		// Sets the position.
		void setPosition(int x, int y);
		// Sets the scale.
		void setScale(float scale);
		// Updates the position by the given value.
		void move(int dx, int dy);
		// Updates the scale by the given value.
		void stretch(float dScale);
	protected:
		int x;
		int y;
		double scale;
	};
}
