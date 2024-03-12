#pragma once

#include <iostream>
#include <SDL_ttf.h>
#include <TextureManager.h>

class Points {
public:
	int score;
	int prevScore;

	Points() {
		font = TTF_OpenFont("./fonts/VCR_OSD_MONO.ttf", 32);
		if (!font) {
			std::cout << "Font failed to load\n";
		}
		textColour = { 255, 255, 255 };
		score = 0;
		prevScore = -1;
		setTex(textTex, "POINTS: 0");
		SDL_QueryTexture(textTex, NULL, NULL, &destRect.w, &destRect.h);
		destRect.x = 1336 - destRect.w - 32;
		destRect.y = 16;
	}

	~Points() {
		SDL_DestroyTexture(textTex);
		TTF_CloseFont(font);
	}

	void update() {
		SDL_DestroyTexture(textTex);
		setTex(textTex, ("POINTS: " + std::to_string(score)).c_str());
		prevScore = score;
	}

	void draw() {
		TextureManager::DrawTexture(textTex, destRect);
	}

private:
	TTF_Font* font;
	SDL_Colour textColour;
	SDL_Texture* textTex;
	SDL_Rect destRect; 

	void setTex(SDL_Texture* tex, const char* text) {
		textTex = TextureManager::LoadTexture(font, textColour, text);
	}
};
