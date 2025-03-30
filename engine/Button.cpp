#include "Button.h"

Button::Button(
	std::string inStr, int x, int y, int w, int h, float scale, SDL_Colour defColour,
	SDL_Colour hoverColour, SDL_Colour textColour, std::function<void()> func
) {
	content = inStr;

	buttonRect.x = x;
	buttonRect.y = y;
	buttonRect.w = w;
	buttonRect.h = h;

	this->defColour = defColour;
	this->hoverColour = hoverColour;
	this->textColour = textColour;
	this->scale = scale;

	pressFunc = func;
}

Button::Button(
	std::string inStr, int x, int y, int w, int h, float scale, std::function<void()> func
) {
	content = inStr;

	buttonRect.x = x;
	buttonRect.y = y;
	buttonRect.w = w;
	buttonRect.h = h;

	defColour = { 0, 0, 255, 255 };
	hoverColour = { 0, 255, 255, 255 };
	textColour = { 255, 255, 255, 255 };
	this->scale = scale;

	pressFunc = func;
}

Button::Button(std::string inStr, int x, int y, int w, int h, std::function<void()> func) {
	content = inStr;

	buttonRect.x = x;
	buttonRect.y = y;
	buttonRect.w = w;
	buttonRect.h = h;

	defColour = { 0, 0, 255, 255 };
	hoverColour = { 0, 255, 255, 255 };
	textColour = { 255, 255, 255, 255 };
	scale = 1.0f;

	pressFunc = func;
}

Button::~Button() {
	SDL_DestroyTexture(texture);
}

void Button::init() {
	transform = &entity->addComponent<Transform>(
		(float)buttonRect.x, (float)buttonRect.y, buttonRect.w, buttonRect.h, scale
	);
	collider = &entity->addComponent<Collider>(
		"button",
		[this](Collider& other) {
			setTex(hoverColour);

			if (MouseTracker::getMouseButtonPressed()) {
				isPressed = true;
			}
			if (MouseTracker::getMouseButtonPressed() || !isPressed) return;

			pressFunc();
			isPressed = false;
		},
		true,
		false,
		false,
		true
	);
	text = &entity->addComponent<Text>(content, buttonRect.x, buttonRect.y, scale, textColour);
	text->centreText(buttonRect);

	setTex(defColour);
	manager.addToGroup(entity, BUTTONS);
}

void Button::update() {
	SDL_DestroyTexture(texture);
	setTex(defColour);
	if (content == "PAUSE") return;
	// std::cout << std::boolalpha << collider->isColliding(MOUSE_TAG) << '\n';
}

void Button::reload() {
	setTex(defColour);
	isPressed = false;
}

void Button::draw() {
	TextureManager::DrawTexture(texture, buttonRect);
}

void Button::setTex(SDL_Colour& colour) {
	texture = TextureManager::LoadTexture(buttonRect, colour);
}
