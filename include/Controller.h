#pragma once

#include <Game.h>
#include <ECS.h>
#include <Components.h>

class Controller : public Component {
public:
	Transform* transform;

	void init() override { transform = &entity->getComponent<Transform>(); }

	void update() override {
		if (Game::event.type != SDL_KEYDOWN) return;

		switch (Game::event.key.keysym.sym) {
		case SDLK_w:
			transform->vel.x = 0;
			transform->vel.y = -1;
			break;
		case SDLK_s:
			transform->vel.x = 0;
			transform->vel.y = 1;
			break;
		case SDLK_a:
			transform->vel.y = 0;
			transform->vel.x = -1;
			break;
		case SDLK_d:
			transform->vel.y = 0;
			transform->vel.x = 1;
		default:
			break;
		}
	}
};

