#pragma once

#include <SDL2/SDL_ttf.h>
#include <TextureManager.h>

class Text {
public:
	Text(std::string inStr, int x, int y, float scale, SDL_Color color) {
		textColour = color;
		data = inStr;
		this->scale = scale;
		destRect.x = x;
		destRect.y = y;
		setTex(textTex, data.c_str());
	}

	Text(std::string inStr, int x, int y, float scale) {
		textColour = { 255, 255, 255 };
		data = inStr;
		this->scale = scale;
		destRect.x = x;
		destRect.y = y;
		setTex(textTex, data.c_str());
	}

	Text(std::string inStr, int x, int y) {
		textColour = { 255, 255, 255 };
		data = inStr;
		scale = 1.0f;
		destRect.x = x;
		destRect.y = y;
		setTex(textTex, data.c_str());
	}

	virtual ~Text() {
		SDL_DestroyTexture(textTex);
	}

	virtual void update() {
		SDL_DestroyTexture(textTex);
		setTex(textTex, data.c_str());
	}

	virtual void draw() {
		SDL_QueryTexture(textTex, NULL, NULL, &destRect.w, &destRect.h);
		destRect.h *= scale;
		destRect.w *= scale;
		TextureManager::DrawTexture(textTex, destRect);
	}

	void setTex(SDL_Texture* tex, const char* text) {
		textTex = TextureManager::LoadTexture(textColour, text);
	}

protected:
	std::string data;
	float scale;
	SDL_Texture* textTex;
	SDL_Colour textColour;
	SDL_Rect destRect; 
};
