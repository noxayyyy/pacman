#include "Collider.h"

Collider::Collider(
	std::string tag, std::function<void(Collider& other)> onCollision, bool isTrigger,
	bool isStatic, bool considerVel, bool isUi
) {
	this->tag = tag;
	collFunc = onCollision;
	this->isTrigger = isTrigger;
	this->isStatic = isStatic;
	this->considerVel = considerVel;
	this->isUi = isUi;
}

Collider::Collider(std::string tag) {
	this->tag = tag;
	collFunc = [](Collider& other) {
	};
	isTrigger = false;
	isStatic = true;
	considerVel = false;
	isUi = false;
}

Collider::~Collider() {
	transform = nullptr;
}

void Collider::init() {
	transform = &entity->addComponent<Transform>();
	collider.x = (int)(transform->pos.x);
	collider.y = (int)(transform->pos.y);
	collider.w = (int)((float)transform->width * transform->scale);
	collider.h = (int)((float)transform->height * transform->scale);
	entity->addGroup(COLLIDERS);
}

void Collider::update() {
	collider.x = (int)(transform->pos.x);
	collider.y = (int)(transform->pos.y);
	collider.w = (int)((float)transform->width * transform->scale);
	collider.h = (int)((float)transform->height * transform->scale);
	if (isStatic) return;
	for (auto& e : colliders) {
		if (!e->hasComponent<Collider>() || !e->hasGroup(COLLIDERS))
			break; // edge case on forced reload where loop still ongoing caused segfault
		if (!e->isActive()) continue;
		if (e->getID() == entity->getID()) continue;
		Collider other = e->getComponent<Collider>();
		if (!checkCollision(other)) continue;
		if (!other.isTrigger) {
			transform->vel.zero();
		}
		onCollision(other);
	}
}

void Collider::onCollision(Collider& other) {
	collFunc(other);
}

const bool Collider::isColliding(std::string collTag) {
	for (auto& e : colliders) {
		Collider other = e->getComponent<Collider>();

		if (other.tag != collTag) continue;
		if (checkCollision(other)) return true;
	}
	return false;
}

const bool Collider::checkCollision(Collider& other) const {
	if (isUi) {
		return other.tag != MOUSE_TAG ? false : AABB(other);
	}
	return other.considerVel ? AABBvel(other) : AABB(other);
}

bool Collider::AABB(const SDL_Rect& otherRect) const {
	return collider.x + collider.w >= otherRect.x && otherRect.x + otherRect.w >= collider.x &&
		   collider.y + collider.h >= otherRect.y && otherRect.y + otherRect.h >= collider.y;
}

bool Collider::AABB(const Collider& otherColl) const {
	return AABB(otherColl.collider);
}

bool Collider::AABBvel(const Collider& otherColl) const {
	SDL_Rect otherRect = otherColl.collider;
	Vector2D vel = transform->vel;

	return collider.x + collider.w + vel.x >= otherRect.x &&
		   collider.y + collider.h + vel.y >= otherRect.y &&
		   otherRect.x + otherRect.w >= collider.x + vel.x &&
		   otherRect.y + otherRect.h >= collider.y + vel.y;
}
