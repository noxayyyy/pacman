#pragma once

#include <SDL2/SDL.h>
#include <Vector2D.h>
#include <Collider.h>

class Collision {
public:
	// Access Aligned Bounding Box Method
	
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
		return
			rectA.x + rectA.w >= rectB.x &&
			rectB.x + rectB.w >= rectA.x &&
			rectA.y + rectA.h >= rectB.y &&
			rectB.y + rectB.h >= rectA.y
		;
	}

	static bool AABB(const Collider& colliderA, const Collider& colliderB) {
		return AABB(colliderA.collider, colliderB.collider);
	}

	static bool AABBvel(const Collider& colliderA, const Collider& colliderB) {
		SDL_Rect rectA = colliderA.collider;
		SDL_Rect rectB = colliderB.collider;
		Vector2D velA = colliderA.transform->vel;

		return
			rectA.x + rectA.w + velA.x >= rectB.x &&
			rectA.y + rectA.h + velA.y>= rectB.y &&
			rectB.x + rectB.w >= rectA.x + velA.x &&
			rectB.y + rectB.h >= rectA.y + velA.y
		;
	}
};
