#include "TextureManager.h"
#include <SDL2/SDL_render.h>

SDL_Point TextureManager::GetSizeOfSurface(const char* fileName) {
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	SDL_Point out = { tmpSurface->w, tmpSurface->h };
	SDL_FreeSurface(tmpSurface);

	return out;
}

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	if (!tmpSurface) {
		return nullptr;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}

SDL_Texture* TextureManager::LoadTexture(const SDL_Colour colour, const char* text) {
	if (!font) {
		std::cout << text << " font failed to load\n";
	}
	SDL_Surface* tmpSurface = TTF_RenderText_Solid(font, text, colour);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}

SDL_Texture* TextureManager::LoadTexture(SDL_Rect& rect, SDL_Colour colour) {
	SDL_Surface* tmpSurface =
		SDL_CreateRGBSurfaceWithFormat(0, rect.w, rect.h, 32, SDL_PIXELFORMAT_RGBA8888);
	SDL_FillRect(
		tmpSurface, NULL, SDL_MapRGBA(tmpSurface->format, colour.r, colour.g, colour.b, colour.a)
	);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}

void TextureManager::DrawTexture(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

void TextureManager::DrawTexture(SDL_Texture* tex, SDL_Rect& dest) {
	SDL_RenderCopy(Game::renderer, tex, NULL, &dest);
}

void TextureManager::DrawTexture(
	SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dest, const double angle
) {
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, angle, NULL, SDL_FLIP_NONE);
}

void TextureManager::DrawTexture(SDL_Texture* tex, SDL_Rect& dest, const double angle) {
	SDL_RenderCopyEx(Game::renderer, tex, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}
