#pragma once

#include <Components.h>
#include <Vector2D.h>

struct Transform : public Component {
	Vector2D pos, vel;
	int height = 50;
	int width = 50;
	float scale = 0.6f;
	int speed = 3;

	Transform() { pos.zero(); }

	Transform(float x, float y) {
		pos.x = x;
		pos.y = y;
	}

	Transform(float scale) {
		pos.zero();
		this->scale = scale;
	}

	Transform(float x, float y, int h, int w, float scale) {
		pos.x = x;
		pos.y = y;
		height = h;
		width = w;
		this->scale = scale;
	}

	Transform(Vector2D vec) { pos = vec; }

	void init() override { vel.zero(); }

	void update() override {
		pos.x += vel.x * speed;
		pos.y += vel.y * speed;
	}
};
