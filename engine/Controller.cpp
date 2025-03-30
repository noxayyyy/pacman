#include "Controller.h"

Controller::Controller() {}

Controller::~Controller() {
	transform = nullptr;
	collider = nullptr;
}

void Controller::init() {
	transform = &entity->addComponent<Transform>();
	collider = &entity->getComponent<Collider>();
	if (!collider) {
		throw SIGSEGV;
	}
}

void Controller::updateKeyDown(SDL_Keycode key) {
	if (KEY_STATES.find(key) == KEY_STATES.end()) return;
	KEY_STATES[key] = true;
}

void Controller::updateKeyUp(SDL_Keycode key) {
	if (KEY_STATES.find(key) == KEY_STATES.end()) return;
	KEY_STATES[key] = false;
}

void Controller::update() {
	if (Game::getPaused()) {
		lastVel.zero();
	}
	lastVel = transform->vel;
	lastAngle = transform->angle;

	if (KEY_STATES[SDLK_w]) {
		transform->vel.x = 0;
		transform->vel.y = -1;
		transform->setAngle(-90);
	}
	if (KEY_STATES[SDLK_a]) {
		transform->vel.x = -1;
		transform->vel.y = 0;
		transform->setAngle(180);
	}
	if (KEY_STATES[SDLK_s]) {
		transform->vel.x = 0;
		transform->vel.y = 1;
		transform->setAngle(90);
	}
	if (KEY_STATES[SDLK_d]) {
		transform->vel.x = 1;
		transform->vel.y = 0;
		transform->setAngle(0);
	}

	if (lastVel == transform->vel) return;

	if (collider->isColliding(WALL_TAG)) {
		transform->vel = lastVel;
		transform->angle = lastAngle;
	}
}

void Controller::reload() {
	for (auto& key : KEY_STATES) {
		key.second = false;
	}
}
