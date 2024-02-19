#include <Collision.h>
#include <Collider.h>
#include <Map.h>

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	if (rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y) return true;
	return false;
}

bool Collision::AABB(const Collider& colliderA, const Collider& colliderB) {
	if (AABB(colliderA.collider, colliderB.collider)) {
		std::cout << colliderA.tag << " hit: " << colliderB.tag << '\n';
		return true;
	}
	return false;
}

bool Collision::AABBvel(const Collider& colliderA, const Collider& colliderB) {
	SDL_Rect rectA = colliderA.collider;
	SDL_Rect rectB = colliderB.collider;
	Vector2D velA = colliderA.transform->vel;

	if (rectA.x + rectA.w + velA.x >= rectB.x &&
		rectA.y + rectA.h + velA.y>= rectB.y &&
		rectB.x + rectB.w >= rectA.x + velA.x &&
		rectB.y + rectB.h >= rectA.y + velA.y) return true;
	return false;
}
