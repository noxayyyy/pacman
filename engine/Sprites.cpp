#include "Sprites.h"

Sprites::Sprites(const char* tex) {
	setTex(tex);
}

Sprites::~Sprites() {
	SDL_DestroyTexture(texture);
}

void Sprites::init() {
	transform = &entity->addComponent<Transform>();
	srcRect.x = srcRect.y = 0;
	srcRect.w = transform->width;
	srcRect.h = transform->height;
}

void Sprites::update() {
	destRect.x = (int)transform->pos.x;
	destRect.y = (int)transform->pos.y;
	destRect.w = transform->width * transform->scale;
	destRect.h = transform->height * transform->scale;
}

void Sprites::draw() {
	TextureManager::DrawTexture(texture, srcRect, destRect, transform->angle);
}

void Sprites::recalcSpriteDimensions() {
	srcRect.w = transform->width;
	srcRect.h = transform->height;
}

void Sprites::setTex(const char* tex) {
	texture = TextureManager::LoadTexture(tex);
}
