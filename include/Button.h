#pragma once

#include "Game.h"
#include <TextureManager.h>
#include <Text.h>
#include <Collider.h>
#include <Collision.h>
#include <functional>

extern Manager manager;

class Button : public Component {
public:
	Button(std::string inStr, int x, int y, int w, int h, float scale, SDL_Colour defColour, SDL_Colour hoverColour, SDL_Colour textColour, std::function<void()> func) {
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

	Button(std::string inStr, int x, int y, int w, int h, float scale, std::function<void()> func)  {
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

	Button(std::string inStr, int x, int y, int w, int h, std::function<void()> func)  {
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

	~Button() {
		SDL_DestroyTexture(texture);
	}

	void init() override {
		transform = &entity->addComponent<Transform>(
			(float)buttonRect.x,
			(float)buttonRect.y,
			buttonRect.w,
			buttonRect.h,
			scale
		);
		collider = &entity->addComponent<Collider>("button");
		text = &entity->addComponent<Text>(content, buttonRect.x, buttonRect.y, scale, textColour);
		text->centreText(buttonRect);

		setTex(defColour);
		manager.addToGroup(entity, Game::BUTTONS);
	}

	void update() override {
		SDL_DestroyTexture(texture);
		if (!Collision::AABB(Game::mouseRect, buttonRect)) {
			setTex(defColour);
			return;
		}
		setTex(hoverColour);
		if (!Game::mouseButtonPressed) {
			isPressed = false;
			return;
		}
		buttonPress();
		isPressed = true;
	}

	void draw() override {
		TextureManager::DrawTexture(texture, buttonRect);
	}

	void buttonPress() {
		if (isPressed) return;
		pressFunc();
	}

private:
	float scale;
	bool isPressed;
	std::string content;
	std::function<void()> pressFunc;

	Transform* transform;
	Collider* collider;
	Text* text;

	SDL_Rect buttonRect;
	SDL_Texture* texture;

	SDL_Colour defColour;
	SDL_Colour hoverColour;
	SDL_Colour textColour;

	void setTex(SDL_Colour& colour) {
		texture = TextureManager::LoadTexture(buttonRect, colour);
	}
};
