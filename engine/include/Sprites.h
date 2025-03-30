#pragma once

#include "ECS.h"
#include "TextureManager.h"
#include "Transform.h"
#include <SDL2/SDL.h>

struct Sprites : public Component {
	friend struct Animator;

public:
	Sprites(const char* tex);
	Sprites(const char* tex, int nFrames, int mSpeed, bool loop);
	~Sprites();

	void init() override;
	void update() override;
	void draw() override;
	void recalcSpriteDimensions();

private:
	Transform* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	void setTex(const char* tex);
};
