#pragma once

#include <SDL.h>
#include <Vector2D.h>
#include <vector>

class Collider;

class Collision {
public: 
	// Access Aligned Bounding Box Method
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const Collider& colliderA, const Collider& colliderB);
	static bool AABBvel(const Collider& colliderA, const Collider& colliderB);
	// static bool checkMove(Vector2D* pos, SDL_Keycode key, float vel);
};