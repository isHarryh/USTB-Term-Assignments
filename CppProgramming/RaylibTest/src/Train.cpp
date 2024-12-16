#include "Train.h"

namespace RaylibTest {
	Train::Train() {
	}

	Train::Train(Color color) {
		mainColor = color;
	}

	void Train::draw() {
		Image img = GenImageColor(1000, 1000, BLANK);

		// Draw shapes
		ImageDrawRectangle(&img, 100, 300, 450, 350, mainColor); // Body
		ImageDrawRectangle(&img, 550, 450, 350, 200, mainColor); // Head
		ImageDrawRectangle(&img, 700, 300, 100, 150, mainColor); // Head
		ImageDrawRectangle(&img, 100, 700, 800, 50, mainColor);  // Wheel

		// Render texture
		BeginDrawing();
		ClearBackground(WHITE);
		Texture tex = LoadTextureFromImage(img);
		DrawTextureEx(tex, Vector2{ (float)x, (float)y }, 0.0f, scale, WHITE);
		EndDrawing();

		// Release resources
		UnloadImage(img);
		UnloadTexture(tex);
	}
}
