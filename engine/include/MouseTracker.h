#pragma once

#include "Collider.h"
#include "ECS.h"
#include "Transform.h"

struct MouseTracker : public Component {
public:
	MouseTracker();
	~MouseTracker();

	void init() override;
	void update() override;
	void reload() override;

	static const bool getMouseButtonPressed();

private:
	Transform* transform;
	Collider* collider;
	static bool isPressed;
};
