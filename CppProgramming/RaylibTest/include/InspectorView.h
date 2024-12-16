#pragma once
#include "GameObject.h"

namespace RaylibTest {
	class InspectorView {
	public:
		InspectorView(GameObject* obj);
		// Draws the inspector view with the wrapped object.
		void draw();
		// Returns true if the inspector should be closed.
		bool shouldClose();
	protected:
		GameObject* obj;
		bool shouldCloseFlag;
	};
}
