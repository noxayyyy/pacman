#pragma once

#include <SDL2/SDL.h>
#include <Vector2D.h>
#include <vector>
#include <Collider.h>

class Collision {
public: 
	// Access Aligned Bounding Box Method
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const Collider& colliderA, const Collider& colliderB);
	static bool AABBvel(const Collider& colliderA, const Collider& colliderB);
};
