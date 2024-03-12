#pragma once

#include <string>
#include <SDL.h>
#include <Components.h>

class Collider : public Component {
public:
	SDL_Rect collider;
	std::string tag;

	Transform* transform;

	Collider(std::string t) { tag = t; }

	void init() override {
		if (!entity->hasComponent<Transform>()) {
			entity->addComponent<Transform>();
		}
		transform = &entity->getComponent<Transform>(); 
		collider.w = (int)((float)transform->width * transform->scale);
		collider.h = (int)((float)transform->height * transform->scale);
	}

	void update() override {
		collider.x = (int)(transform->pos.x);
		collider.y = (int)(transform->pos.y);
	}
};