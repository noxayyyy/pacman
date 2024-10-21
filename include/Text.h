#pragma once

#include "ECS.h"
#include <SDL2/SDL_ttf.h>
#include <TextureManager.h>

class Text : public Component {
public:
	Text(std::string inStr, int x, int y, float scale, SDL_Color color) {
		textColour = color;
		data = inStr;
		this->scale = scale;
		destRect.x = x;
		destRect.y = y;
		setTex(data.c_str());
	}

	Text(std::string inStr, int x, int y, float scale) {
		textColour = { 255, 255, 255, 255 };
		data = inStr;
		this->scale = scale;
		destRect.x = x;
		destRect.y = y;
		setTex(data.c_str());
	}

	Text(std::string inStr, int x, int y) {
		textColour = { 255, 255, 255, 255 };
		data = inStr;
		scale = 1.0f;
		destRect.x = x;
		destRect.y = y;
		setTex(data.c_str());
	}

	~Text() override {
		SDL_DestroyTexture(textTex);
	}

	void update() override {
		SDL_DestroyTexture(textTex);
		setTex(data.c_str());
	}

	void draw() override {
		SDL_QueryTexture(textTex, NULL, NULL, &destRect.w, &destRect.h);
		destRect.h *= scale;
		destRect.w *= scale;
		TextureManager::DrawTexture(textTex, destRect);
	}

	void changeText(std::string text) {
		data = text;
	}

	void centreText(SDL_Rect& parentRect) {
		SDL_QueryTexture(textTex, NULL, NULL, &destRect.w, &destRect.h);

		int diffX = parentRect.w - destRect.w;
		int diffY = parentRect.h - destRect.h;

		destRect.x += diffX / 2;
		destRect.y += diffY / 2;
	}

protected:
	std::string data;
	float scale;
	SDL_Texture* textTex;
	SDL_Colour textColour;
	SDL_Rect destRect;

	void setTex(const char* text) {
		textTex = TextureManager::LoadTexture(textColour, text);
	}
};
