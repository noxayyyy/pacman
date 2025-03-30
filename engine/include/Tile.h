#pragma once

#include "ECS.h"
#include "Sprites.h"
#include "Transform.h"
#include <SDL2/SDL.h>

struct Tile : public Component {
public:
	Transform* transform;
	Sprites* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	Tile(int x, int y, int w, int h, int id);
	~Tile();

	void init() override;
	void resizeTile(int w, int h, float scale = 0.64f);
};
