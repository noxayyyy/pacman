#pragma once

#include <ECS.h>
#include <Tile.h>
#include <Collision.h>
#include <Collider.h>

class Controller {
public:
	Transform* transform;
	Collider* collider;
	Entity* entity;

	Controller(Entity* e) {
		entity = e;
		transform = &entity->getComponent<Transform>();
		collider = &entity->getComponent<Collider>();
	}

	~Controller();

	void updateVel(SDL_Keycode key) {
		switch (key) {
		case SDLK_w:
			transform->vel.x = 0;
			transform->vel.y = -1;
			break;
		case SDLK_a:
			transform->vel.x = -1;
			transform->vel.y = 0;
			break;
		case SDLK_s:
			transform->vel.x = 0;
			transform->vel.y = 1;
			break;
		case SDLK_d:
			transform->vel.x = 1;
			transform->vel.y = 0;
			break;
		default:
			break;
		}
	}
};
