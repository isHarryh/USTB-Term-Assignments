#include <math.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "InspectorView.h"
#include "Plane.h"
#include "Train.h"

using namespace RaylibTest;

int main() {
	// Initialization
	InitWindow(800, 450, "Raylib Test");
	SetTraceLogLevel(LOG_WARNING);
	SetTargetFPS(30);
	GuiSetStyle(DEFAULT, TEXT_SIZE, 18);

	InspectorView* view = nullptr;
	GameObject* obj = nullptr;

	// Render loop
	while (!WindowShouldClose()) {
		if (view == nullptr) {
			// Goto homepage
			BeginDrawing();
			ClearBackground(WHITE);
			DrawText("Homepage", 25, 25, 36, GRAY);
			EndDrawing();

			if (GuiButton(Rectangle { 150, 150, 150, 30 }, "Blue Plane")) {
				obj = new Plane(SKYBLUE);
			}
			if (GuiButton(Rectangle { 150, 250, 150, 30 }, "Blue Train")) {
				obj = new Train(SKYBLUE);
			}
			if (GuiButton(Rectangle{ 450, 150, 150, 30 }, "Green Plane")) {
				obj = new Plane(DARKGREEN);
			}
			if (GuiButton(Rectangle{ 450, 250, 150, 30 }, "Green Train")) {
				obj = new Train(DARKGREEN);
			}
			if (obj != nullptr) {
				obj->setScale(0.25);
				view = new InspectorView(obj);
			}
		} else {
			// Goto inspector
			view->draw();
			if (view->shouldClose()) {
				delete view;
				view = nullptr;
				delete obj;
				obj = nullptr;
			}
		}
	}

	CloseWindow();
	return 0;
}
