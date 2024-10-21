#pragma once

#include <SDL2/SDL.h>
#include <ECS.h>
#include <Transform.h>
#include <TextureManager.h>

class Sprites : public Component {
public:
	Sprites() = default;

	Sprites(const char* tex) {
		setTex(tex);
	}

	~Sprites() {
		SDL_DestroyTexture(texture); 
	}
	
	void init() override {
		transform = &entity->addComponent<Transform>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override {
		destRect.x = (int)transform->pos.x;
		destRect.y = (int)transform->pos.y;
		destRect.w = srcRect.w * transform->scale;
		destRect.h = srcRect.h * transform->scale;
	}

	void draw() override {
		TextureManager::DrawTexture(texture, srcRect, destRect);
	}

private:
	Transform* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	void setTex(const char* tex) {
		texture = TextureManager::LoadTexture(tex); 
	}
};
