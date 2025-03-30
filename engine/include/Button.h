#pragma once

#include "Collider.h"
#include "MouseTracker.h"
#include "Text.h"
#include "TextureManager.h"
#include <functional>

extern Manager manager;

struct Button : public Component {
public:
	Button(
		std::string inStr, int x, int y, int w, int h, float scale, SDL_Colour defColour,
		SDL_Colour hoverColour, SDL_Colour textColour, std::function<void()> func
	);
	Button(std::string inStr, int x, int y, int w, int h, float scale, std::function<void()> func);
	Button(std::string inStr, int x, int y, int w, int h, std::function<void()> func);
	~Button();

	void init() override;
	void update() override;
	void reload() override;
	void draw() override;

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

	void setTex(SDL_Colour& colour);
};
