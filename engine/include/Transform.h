#pragma once

#include "ECS.h"
#include "Game.h"
#include "Vector2D.h"

struct Transform : public Component {
	enum Rotations { NINETY, ONE_EIGHTY };

	Vector2D initPos, pos, vel;
	int height = 50;
	int width = 50;
	float scale = 0.6f;
	float speed = 240.0f; // 480.0f;
	int angle;

	Transform();
	Transform(float x, float y);
	Transform(float scale);
	Transform(float x, float y, int w, int h, float scale);
	Transform(Vector2D vec);

	void init() override;
	void update() override;
	void reload() override;

	void rotate(Rotations rotation, bool anticlockwise);
	void setAngle(double angle);
};
