#include "MouseTracker.h"

MouseTracker::MouseTracker() {
	isPressed = false;
}

MouseTracker::~MouseTracker() {
	transform = nullptr;
	collider = nullptr;
}

void MouseTracker::init() {
	transform = &entity->addComponent<Transform>(0, 0, 0, 0, 1);
	collider =
		&entity->addComponent<Collider>(MOUSE_TAG, [](Collider& other) {}, true, true, false);
}

void MouseTracker::update() {
	transform->pos.x = Game::mouseCoords.x;
	transform->pos.y = Game::mouseCoords.y;
	isPressed = Game::mouseButtonPressed;
}

void MouseTracker::reload() {
	isPressed = false;
}

const bool MouseTracker::getMouseButtonPressed() {
	return isPressed;
}
