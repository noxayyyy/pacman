#pragma once

#include <Game.h>

class TextureManager {
public:
	static TTF_Font* font;

	static SDL_Texture* LoadTexture(const char* fileName) {
		SDL_Surface* tmpSurface = IMG_Load(fileName);
		if (!tmpSurface) {
			return nullptr;
		}
		SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);

		return tex;
	}

	static SDL_Texture* LoadTexture(const SDL_Colour colour, const char* text) {
		if (!font) {
			std::cout << text << " font failed to load\n";
		}
		SDL_Surface* tmpSurface = TTF_RenderText_Solid(font, text, colour);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);

		return tex;
	}

	static SDL_Texture* LoadTexture(SDL_Rect& rect, SDL_Colour colour) {
		SDL_Surface* tmpSurface = SDL_CreateRGBSurfaceWithFormat(
			0,
			rect.w,
			rect.h,
			32,
			SDL_PIXELFORMAT_RGBA8888
		);
		SDL_FillRect(
			tmpSurface,
			NULL,
			SDL_MapRGBA(tmpSurface->format, colour.r, colour.g, colour.b, colour.a)
		);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);

		return tex;
	}

	static void DrawTexture(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dest) {
		SDL_RenderCopy(Game::renderer, tex, &src, &dest);
	}

	static void DrawTexture(SDL_Texture* tex, SDL_Rect& dest) {
		SDL_RenderCopy(Game::renderer, tex, NULL, &dest);
	}
};
