#pragma once

#include <Components.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>

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
			path = "./sprites/path.png";
			break;
		case 1:
			path = "./sprites/wall.png";
			break;
		case 2:
			path = "./sprites/ghost_bar.png";
			break;
		case 3:
			path = "./sprites/pellet.png";
			break;
		default:
			path = "./sprites/path.png";
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
