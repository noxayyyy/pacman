#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <ECS.h>
#include <Transform.h>

class Collider : public Component {
public:
	SDL_Rect collider;
	std::string tag;

	Transform* transform;

	Collider(std::string t) { tag = t; }

	void init() override {
		transform = &entity->addComponent<Transform>();
		collider.w = (int)((float)transform->width * transform->scale);
		collider.h = (int)((float)transform->height * transform->scale);
	}

	void update() override {
		collider.x = (int)(transform->pos.x);
		collider.y = (int)(transform->pos.y);
	}
};
