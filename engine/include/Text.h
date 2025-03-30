#pragma once

#include "ECS.h"
#include "TextureManager.h"
#include <SDL2/SDL_ttf.h>

struct Text : public Component {
public:
	Text(std::string inStr, int x, int y, float scale, SDL_Color color);
	Text(std::string inStr, int x, int y, float scale);
	Text(std::string inStr, int x, int y);

	~Text() override;

	void update() override;
	void draw() override;

	void changeText(std::string text);
	void centreText(SDL_Rect& parentRect);

protected:
	std::string data;
	float scale;
	SDL_Texture* textTex;
	SDL_Colour textColour;
	SDL_Rect destRect;

	void setTex(const char* text);
};
