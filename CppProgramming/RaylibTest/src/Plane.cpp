#include "raylib.h"
#include "Plane.h"

namespace RaylibTest {
	Plane::Plane() {
		mainColor = GRAY;
	}

	Plane::Plane(Color color) {
		mainColor = color;
	}

	void Plane::draw() {
		Image img = GenImageColor(1000, 1000, BLANK);

		// Draw shapes
		ImageDrawRectangle(&img, 150, 450, 650, 100, mainColor);
		ImageDrawTriangle(&img, Vector2{ 800, 450 }, Vector2{ 800, 550 }, Vector2{ 900, 500 }, mainColor); // Head
		ImageDrawTriangle(&img, Vector2{ 100, 400 }, Vector2{ 100, 600 }, Vector2{ 300, 500 }, mainColor); // Tail
		ImageDrawTriangle(&img, Vector2{ 400, 150 }, Vector2{ 400, 450 }, Vector2{ 700, 450 }, mainColor); // Wing
		ImageDrawTriangle(&img, Vector2{ 400, 850 }, Vector2{ 400, 550 }, Vector2{ 700, 550 }, mainColor); // Wing

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
