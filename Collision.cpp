#include <Collision.h>
#include <Collider.h>

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