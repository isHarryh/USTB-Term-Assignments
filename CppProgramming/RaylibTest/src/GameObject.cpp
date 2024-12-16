#include "GameObject.h"

namespace RaylibTest {
	GameObject::GameObject() {
		x = 0;
		y = 0;
		scale = 1.0f;
	}

	void GameObject::draw() {
	}

	void GameObject::setPosition(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void GameObject::setScale(float scale) {
		this->scale = scale;
	}

	void GameObject::stretch(float dScale) {
		this->scale += dScale;
	}

	void GameObject::move(int dx, int dy) {
		this->x += dx;
		this->y += dy;
	}
}
