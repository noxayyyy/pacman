#pragma once

#include <Game.h>

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static SDL_Texture* LoadTexture(const SDL_Colour colour, const char* text);
	static void DrawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	static void DrawTexture(SDL_Texture* tex, SDL_Rect dest);
};
