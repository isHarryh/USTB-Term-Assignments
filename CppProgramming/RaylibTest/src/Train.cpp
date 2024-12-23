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
		ImageDrawRectangle(&img, 100, 250, 500, 400, mainColor); // Body
		ImageDrawRectangle(&img, 600, 450, 350, 200, mainColor); // Head
		ImageDrawRectangle(&img, 750, 300, 100, 150, mainColor); // Head
		ImageDrawRectangle(&img, 100, 700, 850, 50, mainColor);  // Wheel
		ImageDrawRectangle(&img, 200, 350, 100, 100, WHITE); // Window
		ImageDrawRectangle(&img, 400, 350, 100, 100, WHITE); // Window
		ImageDrawCircle(&img, 650, 150, 50, mainColor); // Bubble
		ImageDrawCircle(&img, 750, 250, 25, mainColor); // Bubble

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
