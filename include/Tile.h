#pragma once

#include <Components.h>
#include <SDL.h>
#include <string>

class Tile : public Component {
public:
	Transform* transform;
	Sprites* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	Tile() = default;
	Tile(int x, int y, int w, int h, int id) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID) {
		case 0:
			path = "C:/GameDev/sprites/path.png";
			break;
		case 1:
			path = "C:/GameDev/sprites/wall.png";
			break;
		case 2:
			path = "C:/GameDev/sprites/ghost_bar.png";
			break;
		default:
			path = "C:/GameDev/sprites/path.png";
			break;
		}
	}

	void init() override {
		entity->addComponent<Transform>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 0.64f);
		transform = &entity->getComponent<Transform>();
		entity->addComponent<Sprites>(path);
		sprite = &entity->getComponent<Sprites>();
	}
};