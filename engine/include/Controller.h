#pragma once

#include "Collider.h"
#include "ECS.h"
#include <csignal>

struct Controller : public Component {
public:
	Controller();
	~Controller();

	void init() override;
	void updateKeyDown(SDL_Keycode key);
	void updateKeyUp(SDL_Keycode key);
	void update() override;
	void reload() override;

private:
	Vector2D lastVel;
	int lastAngle;
	Transform* transform;
	Collider* collider;

	std::unordered_map<SDL_Keycode, bool> KEY_STATES {
		{ SDLK_w, false },
		{ SDLK_s, false },
		{ SDLK_a, false },
		{ SDLK_d, false },
	};
};
