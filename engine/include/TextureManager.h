#pragma once

#include "Game.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

struct TextureManager {
public:
	static TTF_Font* font;

	static SDL_Point GetSizeOfSurface(const char* fileName);
	static SDL_Texture* LoadTexture(const char* fileName);
	static SDL_Texture* LoadTexture(const SDL_Colour colour, const char* text);
	static SDL_Texture* LoadTexture(SDL_Rect& rect, SDL_Colour colour);
	static void DrawTexture(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dest);
	static void DrawTexture(SDL_Texture* tex, SDL_Rect& dest);
	static void DrawTexture(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dest, const double angle);
	static void DrawTexture(SDL_Texture* tex, SDL_Rect& dest, const double angle);
};
