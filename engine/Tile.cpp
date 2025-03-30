#include "Tile.h"

Tile::Tile(int x, int y, int w, int h, int id) {
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
		path = "./sprites/test_wall.png";
		break;
	case 2:
		path = "./sprites/ghost_bar.png";
		break;
	case 3:
		path = "./sprites/pellet.png";
		break;
	default:
		path = "./sprites/test_path.png";
		break;
	}
}

Tile::~Tile() {
	transform = nullptr;
	sprite = nullptr;
}

void Tile::init() {
	transform = &entity->addComponent<Transform>(
		(float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 0.64f
	);
	sprite = &entity->addComponent<Sprites>(path);
}

void Tile::resizeTile(int w, int h, float scale) {
	tileRect.w = w;
	tileRect.h = h;

	transform->width = tileRect.w;
	transform->height = tileRect.h;
	transform->scale = scale;
}
