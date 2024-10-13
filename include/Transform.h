#pragma once

#include <ECS.h>
#include <Vector2D.h>
#include <Game.h>

struct Transform : public Component {
	Vector2D initPos, pos, vel;
	int height = 50;
	int width = 50;
	float scale = 0.6f;
	float speed = 240.0f; // 480.0f;

	Transform() { 
		pos.zero(); 
		initPos.zero();
	}

	Transform(float x, float y) {
		initPos.x = pos.x = x;
		initPos.y = pos.y = y;
	}

	Transform(float scale) {
		pos.zero();
		this->scale = scale;
	}

	Transform(float x, float y, int h, int w, float scale) {
		initPos.x = pos.x = x;
		initPos.y = pos.y = y;
		height = h;
		width = w;
		this->scale = scale;
	}

	Transform(Vector2D vec) { 
		initPos = pos = vec; 
	}

	void init() override { 
		vel.zero(); 
	}

	void update() override {
		pos.x += vel.x * speed * Game::deltaTime;
		pos.y += vel.y * speed * Game::deltaTime;
	}

	void reload() override {
		pos = initPos;
		vel.zero();
	}
};
