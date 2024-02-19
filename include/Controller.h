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

	void updateKeyDown(SDL_Keycode key) {
		if (Game::Keys.find(key) == Game::Keys.end())
			return;
		Game::Keys[key] = true;
	}

	void updateKeyUp(SDL_Keycode key) {
		if (Game::Keys.find(key) == Game::Keys.end())
			return;
		Game::Keys[key] = false;
	}

	void updateVel() {
		Vector2D lastVel = transform->vel;
		if (Game::Keys[SDLK_w]) {
			transform->vel.x = 0;
			transform->vel.y = -1;
		}
		if (Game::Keys[SDLK_a]) {
			transform->vel.x = -1;
			transform->vel.y = 0;
		}
		if (Game::Keys[SDLK_s]) {
			transform->vel.x = 0;
			transform->vel.y = 1;
		}
		if (Game::Keys[SDLK_d]) {
			transform->vel.x = 1;
			transform->vel.y = 0;
		}
		Game::collisionResponse(lastVel);
	}
};
