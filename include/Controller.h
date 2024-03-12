#pragma once

#include <ECS.h>
#include <Collision.h>
#include <Collider.h>

class Controller {
public:
	Controller(Entity* e) {
		entity = e;
		transform = &entity->getComponent<Transform>();
		collider = &entity->getComponent<Collider>();
	}

	~Controller() {}

	void updateKeyDown(SDL_Keycode key) {
		if (Game::KeyStates.find(key) == Game::KeyStates.end()) {
			return;
		}
		Game::KeyStates[key] = true;
	}

	void updateKeyUp(SDL_Keycode key) {
		if (Game::KeyStates.find(key) == Game::KeyStates.end()) {
			return;
		}
		Game::KeyStates[key] = false;
	}

	void updateVel() {
		Vector2D lastVel = transform->vel;
		if (Game::KeyStates[SDLK_w]) {
			transform->vel.x = 0;
			transform->vel.y = -1;
		}
		if (Game::KeyStates[SDLK_a]) {
			transform->vel.x = -1;
			transform->vel.y = 0;
		}
		if (Game::KeyStates[SDLK_s]) {
			transform->vel.x = 0;
			transform->vel.y = 1;
		}
		if (Game::KeyStates[SDLK_d]) {
			transform->vel.x = 1;
			transform->vel.y = 0;
		}
		Game::collisionResponse(lastVel);
	}

private:
	Transform* transform;
	Collider* collider;
	Entity* entity;
};
