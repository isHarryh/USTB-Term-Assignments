#include "InspectorView.h"

#include "raylib.h"
#include "raygui.h"

#define W 800
#define H 450
#define STEP_P 5
#define STEP_S 0.02

namespace RaylibTest {
	InspectorView::InspectorView(GameObject* obj) {
		this->obj = obj;
		this->shouldCloseFlag = false;
	}

	void InspectorView::draw() {
		// Draw the object
		obj->draw();

		// Show moving controls
		if (GuiButton(Rectangle{ 20, H - 90, 90, 30 }, "A") || IsKeyPressed('A') || IsKeyPressed(KEY_LEFT)) {
			obj->move(-STEP_P, 0);
		}
		if (GuiButton(Rectangle{ 220, H - 90, 90, 30 }, "D") || IsKeyPressed('D') || IsKeyPressed(KEY_RIGHT)) {
			obj->move(STEP_P, 0);
		}
		if (GuiButton(Rectangle{ 120, H - 130, 90, 30 }, "W") || IsKeyPressed('W') || IsKeyPressed(KEY_UP)) {
			obj->move(0, -STEP_P);
		}
		if (GuiButton(Rectangle{ 120, H - 50, 90, 30 }, "S") || IsKeyPressed('S') || IsKeyPressed(KEY_DOWN)) {
			obj->move(0, STEP_P);
		}

		// Show scaling controls
		if (GuiButton(Rectangle{ W - 140, H - 110, 100, 30 }, "Size +") || IsKeyPressed('=')) {
			obj->stretch(STEP_S);
		}
		if (GuiButton(Rectangle{ W - 140, H - 70, 100, 30 }, "Size -") || IsKeyPressed('-')) {
			obj->stretch(-STEP_S);
		}

		// Show exit controls
		if (GuiButton(Rectangle{ W - 140, 50, 100, 30 }, "< Back") || IsKeyPressed(KEY_BACKSPACE)) {
			shouldCloseFlag = true;
		}
	}

	bool InspectorView::shouldClose() {
		return shouldCloseFlag;
	}
}
