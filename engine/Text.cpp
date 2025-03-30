#include "Text.h"

Text::Text(std::string inStr, int x, int y, float scale, SDL_Color color) {
	textColour = color;
	data = inStr;
	this->scale = scale;
	destRect.x = x;
	destRect.y = y;
	setTex(data.c_str());
}

Text::Text(std::string inStr, int x, int y, float scale) {
	textColour = { 255, 255, 255, 255 };
	data = inStr;
	this->scale = scale;
	destRect.x = x;
	destRect.y = y;
	setTex(data.c_str());
}

Text::Text(std::string inStr, int x, int y) {
	textColour = { 255, 255, 255, 255 };
	data = inStr;
	scale = 1.0f;
	destRect.x = x;
	destRect.y = y;
	setTex(data.c_str());
}

Text::~Text() {
	SDL_DestroyTexture(textTex);
}

void Text::update() {
	SDL_DestroyTexture(textTex);
	setTex(data.c_str());
}

void Text::draw() {
	SDL_QueryTexture(textTex, NULL, NULL, &destRect.w, &destRect.h);
	destRect.h *= scale;
	destRect.w *= scale;
	TextureManager::DrawTexture(textTex, destRect);
}

void Text::changeText(std::string text) {
	data = text;
}

void Text::centreText(SDL_Rect& parentRect) {
	SDL_QueryTexture(textTex, NULL, NULL, &destRect.w, &destRect.h);

	int diffX = parentRect.w - destRect.w;
	int diffY = parentRect.h - destRect.h;

	destRect.x += diffX / 2;
	destRect.y += diffY / 2;
}

void Text::setTex(const char* text) {
	textTex = TextureManager::LoadTexture(textColour, text);
}
