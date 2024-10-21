#include "Build.h"
#include <Map.h>
#include <SceneManager.h>

extern Manager manager;
extern SceneManager sceneManager;

std::vector<BuilderSpawner> spawners;

const char Map::path;
const char Map::blank;
const char Map::wall;
const char Map::ghostBar;
const char Map::ghostSpawn;
const int Map::spawnerCount;
int Map::pelletCount = 0;

Map::Map() = default;

Map::~Map() = default;

void Map::init() {
	img.clear(blank);

	spawners.push_back(BuilderSpawner());
	spawners.push_back(BuilderSpawner());

	colourMap[blank] = 0;
	colourMap[wall] = 1;
	colourMap[ghostBar] = 2;
	colourMap[path] = 3;
	colourMap[ghostSpawn] = 4;
}

void Map::addWalls(int x, int y) {
	for (int i = -1; i < 2; i++) {
		if (y + i >= img.height() || y + i < 0) continue;
		for (int j = -1; j < 2; j++) {
			if (x + j >= img.width() || x + j < 0) continue;
			if (img(y + i, x + j) != path &&
				img(y + i, x + j) != ghostBar &&
				img(y + i, x + j) != ghostSpawn) {
				img(y + i, x + j) = wall;
			}
		}
	}
}

void Map::updateImg(BuilderSpawner& spawner, std::vector<bool> killPrevBlock) {
	int counter = 0;
	for (auto& builder : spawner.builders) {
		img(builder.y, builder.x) = path;

		switch (builder.currDir) {
		case Builder::UP:
			img(builder.y + 1, builder.x) = path;
			break;
		case Builder::DOWN:
			img(builder.y - 1, builder.x) = path;
			break;
		case Builder::LEFT:
			img(builder.y, builder.x + 1) = path;
			break;
		case Builder::RIGHT:
			img(builder.y, builder.x - 1) = path;
			break;
		default:
			break;
		}

		if (killPrevBlock[counter++]) {
			img(builder.y, builder.x) = blank;
		}
	}
}

std::vector<bool> updateSpawnerActivities(Map::MapArray imgArr, BuilderSpawner& spawner) {
	std::vector<bool> killPrevBlock = { false, false, false };
	int count = 0;
	for (auto& builder : spawner.builders) {
		char currBlock = imgArr(builder.y, builder.x);
		char prevBlock;

		switch (builder.currDir) {
		case Builder::UP:
			prevBlock = imgArr(builder.y + 1, builder.x);
			break;
		case Builder::DOWN:
			prevBlock = imgArr(builder.y - 1, builder.x);
			break;
		case Builder::LEFT:
			prevBlock = imgArr(builder.y, builder.x + 1);
			break;
		case Builder::RIGHT:
			prevBlock = imgArr(builder.y, builder.x - 1);
			break;
		default:
			return std::vector<bool>(false);
		}
		killPrevBlock[count++] = builder.updateActivity(currBlock, prevBlock);
	}
	return killPrevBlock;
}

bool checkSpawnerActivities(std::vector<BuilderSpawner>& spawners) {
	for (auto& spawn : spawners) {
		if (spawn.isActive()) {
			return true;
		}
	}
	return false;
}

void Map::addPassthrough() {
	int x = rand() % 18 + 4;
	while (img(x, 18) != path || img(x - 1, 19) == path || img(x + 1, 19) == path) {
		x = rand() % 18 + 4;
	}
	img(x, 19) = path;
}

void Map::addSpawnBox() {
	img(1, 17) = img(1, 18) = img(1, 19) = ghostSpawn;
	img(3, 19) = path;
	img(2, 19) = ghostBar;
}

void Map::drawMap() {
	srand(time(0));

	spawners[0].x = spawners[1].x = 10;
	spawners[0].y = 3;
	spawners[1].y = MAP_HEIGHT - 3;

	for (auto& spawn : spawners) {
		spawn.builders[0].x = spawn.x + 8;
		spawn.builders[1].x = spawn.x - 8;
		spawn.builders[2].x = spawn.x;

		spawn.builders[0].y = spawn.builders[1].y = spawn.y;
	}

	spawners[0].builders[2].y = spawners[0].y + 2;
	spawners[1].builders[2].y = spawners[1].y - 2;

	for (int i = 0; i < 3; i++) {
		spawners[0].builders[i].currDir = Builder::DOWN;
		spawners[1].builders[i].currDir = Builder::UP;
	}
	addSpawnBox();

	for (int i = spawners[0].x - 8; i < spawners[0].x + 9; i++) {
		img(spawners[0].y, i) = path;
		img(spawners[1].y, i) = path;
	}
	for (int i = 0; i < 3; i++) {
		img(spawners[0].y + i, spawners[0].x) = path;
		img(spawners[1].y - i, spawners[0].x) = path;
	}
	

	int i = 0;
	while (checkSpawnerActivities(spawners)) {
		int j = i % spawnerCount;
		i++;

		std::vector<bool> killPrevBlock = { false, false, false };
		spawners[j].moveBuilders();
		killPrevBlock = updateSpawnerActivities(img, spawners[j]);
		updateImg(spawners[j], killPrevBlock);
		spawners[j].updateBuilders();
	}

	for (int y = 0; y < img.height() - 2; y++) {
		for (int x = 0; x < img.width(); x++) {
			if (img(y, x) != path && img(y, x) != ghostSpawn) continue;
			addWalls(x, y);
		}
	}

	for (int i = 0; i < 3; i++) {
		addPassthrough();
	}
}

int Map::colourReference(char colour) {
	if (colourMap.find(colour) != colourMap.end()) {
		return colourMap[colour];
	}
	return 4;
}

void Map::addTile(int id, int x, int y) {
	auto& tile(manager.addEntity("tile"));
	tile.addComponent<Tile>(x, y, 50, 50, id);
	switch (id) {
	case 0:
		tile.addComponent<Collider>("null");
		return;
	case 1:
		tile.addComponent<Collider>("wall");
		tile.addGroup(Game::COLLIDERS);
		break;
	case 2:
		tile.addComponent<Collider>("ghostBar");
		tile.addGroup(Game::GHOST_BAR);
		break;
	case 3:
		tile.addComponent<Collider>("pellet");
		tile.addGroup(Game::PELLETS);
		tile.addGroup(Game::COLLIDERS);
		pelletCount++;
		break;
	case 4:
		tile.addComponent<Collider>("path");
		break;
	default:
		std::cout << "Invalid Tile ID: " << id << '\n';
		return;
	}
	tile.addGroup(Game::MAP);
	sceneManager.getCurrentScene()->addEntityToScene(tile);
}

void Map::loadMap() {
	int pixelVal;
	int xpos, ypos;

	for (int x = 0; x < img.width(); x++) {
		for (int y = 0; y < img.height(); y++) {
			pixelVal = colourReference(img(y, x));
			xpos = x * 32 + PADDING_X;
			ypos = y * 32 + PADDING_Y;

			addTile(pixelVal, xpos, ypos);
			if (x == img.width() - 1) continue;

			xpos += (img.width() - x) * 64 - 64;
			addTile(pixelVal, xpos, ypos);
		}
	}
}

void Map::reloadMap() {
	spawners.clear();
	pelletCount = 0;

	init();
	drawMap();
	loadMap();
}
