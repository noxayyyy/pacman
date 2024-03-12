#include <TextureManager.h>

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tex;
}

SDL_Texture* TextureManager::LoadTexture(TTF_Font* font, const SDL_Colour colour, const char* text) {
	SDL_Surface* tmpSurface = TTF_RenderText_Solid(font, text, colour);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tex;
} 

void TextureManager::DrawTexture(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) { 
	SDL_RenderCopy(Game::renderer, tex, &src, &dest); 
}

void TextureManager::DrawTexture(SDL_Texture* tex, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, NULL, &dest);
}