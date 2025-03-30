#pragma once

#include "Constants.h"
#include "ECS.h"
#include "Transform.h"
#include <SDL2/SDL.h>
#include <functional>
#include <string>

extern std::vector<Entity*>& colliders;

struct Collider : public Component {
public:
	std::string tag;

	Collider(
		std::string tag, std::function<void(Collider& other)> onCollision, bool isTrigger = false,
		bool isStatic = false, bool considerVel = false, bool isUi = false
	);
	Collider(std::string tag);
	~Collider();

	void init() override;
	void update() override;
	void onCollision(Collider& other);
	const bool isColliding(std::string collTag);

private:
	SDL_Rect collider;
	std::function<void(Collider& other)> collFunc;
	Transform* transform;
	bool considerVel;
	bool isTrigger;
	bool isStatic;
	bool isUi;

	const bool checkCollision(Collider& other) const;
	bool AABB(const SDL_Rect& otherRect) const;
	bool AABB(const Collider& otherColl) const;
	bool AABBvel(const Collider& otherColl) const;
};
