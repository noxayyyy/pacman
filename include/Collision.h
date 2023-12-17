#pragma once

#include <SDL.h>

class Collider;

class Collision {
public:
	// Access Aligned Bounding Box Method
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB); 
	static bool AABB(const Collider& colliderA, const Collider& colliderB);
};