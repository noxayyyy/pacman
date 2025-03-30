#include "Map.h"
#include "Constants.h"
#include "SceneManager.h"
#include "UserConstants.h"

extern Manager manager;
extern SceneManager sceneManager;

std::vector<BuilderSpawner> spawners;

int Map::pelletCount = 0;

Map::Map() : tileSet(MAP_SIZE.x * 2, MAP_SIZE.y * 2, nullptr) {}

Map::~Map() = default;

void Map::init() {
	img.clear(BLANK);
	tileSet.clear(nullptr);

	spawners.emplace_back(BuilderSpawner());
	spawners.emplace_back(BuilderSpawner());

	colourMap[BLANK] = 0;
	colourMap[WALL] = 1;
	colourMap[GHOST_BAR_CHAR] = 2;
	colourMap[PATH] = 3;
	colourMap[GHOST_SPAWN] = 4;
}

void Map::addWalls(int x, int y) {
	for (int i = -1; i < 2; i++) {
		if (y + i >= img.height() || y + i < 0) continue;
		for (int j = -1; j < 2; j++) {
			if (x + j >= img.width() || x + j < 0) continue;
			if (img(y + i, x + j) != PATH && img(y + i, x + j) != GHOST_BAR_CHAR &&
				img(y + i, x + j) != GHOST_SPAWN) {
				img(y + i, x + j) = WALL;
			}
		}
	}
}

void Map::updateImg(BuilderSpawner& spawner, std::vector<bool> killPrevBlock) {
	int counter = 0;
	for (auto& builder : spawner.builders) {
		img(builder.y, builder.x) = PATH;

		switch (builder.currDir) {
		case Builder::UP:
			img(builder.y + 1, builder.x) = PATH;
			break;
		case Builder::DOWN:
			img(builder.y - 1, builder.x) = PATH;
			break;
		case Builder::LEFT:
			img(builder.y, builder.x + 1) = PATH;
			break;
		case Builder::RIGHT:
			img(builder.y, builder.x - 1) = PATH;
			break;
		default:
			break;
		}

		if (killPrevBlock[counter++]) {
			img(builder.y, builder.x) = BLANK;
		}
	}
}

std::vector<bool> updateSpawnerActivities(Map::MapArray<char> imgArr, BuilderSpawner& spawner) {
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

void Map::addCollPass() {
	int y = rand() % 18 + 4;
	while (img(y, 18) != PATH || img(y - 1, 19) == PATH || img(y + 1, 19) == PATH) {
		y = rand() % 18 + 4;
	}
	img(y, 19) = PATH;
}

void Map::addRowPass(int y) {
	int x = rand() % (MAP_SIZE.x - 3) + 2;
	while (img(y - 1, x) != PATH || img(y + 1, x) != PATH || img(y, x - 1) == PATH ||
		   img(y, x + 1) == PATH) {
		x = rand() % (MAP_SIZE.x - 3) + 2;
	}
	img(y, x) = PATH;
}

void Map::addSpawnBox() {
	img(1, 17) = img(1, 18) = img(1, 19) = GHOST_SPAWN;
	img(3, 19) = PATH;
	img(2, 19) = GHOST_BAR_CHAR;
}

void Map::drawMap() {
	srand(time(0));

	spawners[0].x = spawners[1].x = 10;
	spawners[0].y = 3;
	spawners[1].y = MAP_SIZE.y - 3;

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
		img(spawners[0].y, i) = PATH;
		img(spawners[1].y, i) = PATH;
	}
	for (int i = 0; i < 3; i++) {
		img(spawners[0].y + i, spawners[0].x) = PATH;
		img(spawners[1].y - i, spawners[0].x) = PATH;
	}

	int i = 0;
	while (checkSpawnerActivities(spawners)) {
		int j = i % SPAWNER_COUNT;
		i++;

		std::vector<bool> killPrevBlock = { false, false, false };
		spawners[j].moveBuilders();
		killPrevBlock = updateSpawnerActivities(img, spawners[j]);
		updateImg(spawners[j], killPrevBlock);
		spawners[j].updateBuilders();
	}

	for (int y = 0; y < img.height() - 2; y++) {
		for (int x = 0; x < img.width(); x++) {
			if (img(y, x) != PATH && img(y, x) != GHOST_SPAWN) continue;
			addWalls(x, y);
		}
	}

	for (int i = 0; i < 3; i++) {
		addCollPass();
	}

	int y = 3;
	for (; y < MAP_SIZE.y - 3; y++) {
		bool hasGap = false;
		for (int j = 1; j < MAP_SIZE.x - 2; j++) {
			if (img(y, j) != PATH) continue;
			hasGap = true;
			break;
		}
		if (!hasGap) break;
	}
	if (y == MAP_SIZE.y - 3) return;
	for (int i = 0; i < 2; i++) {
		addRowPass(y);
	}
}

int Map::colourReference(char colour) {
	if (colourMap.find(colour) != colourMap.end()) {
		return colourMap[colour];
	}
	return 4;
}

void Map::addTile(int id, int x, int y) {
	Entity& tile(manager.addEntity("tile"));
	tile.addComponent<Tile>(x, y, 50, 50, id);
	switch (id) {
	case 0:
		std::cout << "oop\n";
		// tile.addComponent<Collider>("null");
		return;
	case 1:
		tile.addComponent<Collider>(WALL_TAG, [](Collider& other) {}, false, true, true, false);
		break;
	case 2:
		// tile.addComponent<Collider>("ghostBar");
		tile.addGroup(GHOST_BAR);
		break;
	case 3:
		tile.addComponent<Collider>(PELLET_TAG, [](Collider& other) {}, true, true, false, false);
		tile.addGroup(PELLETS);
		pelletCount++;
		break;
	case 4:
		// tile.addComponent<Collider>("path");
		break;
	default:
		std::cout << "Invalid Tile ID: " << id << '\n';
		return;
	}
	tileSet((y - MAP_PADDING.y) / 32, (x - MAP_PADDING.x) / 32) = &tile;
	tile.addGroup(MAP);
	sceneManager.getCurrentScene()->addEntityToScene(tile);
}

int Map::optimiseHelper(int x, int y, GroupID antiGroup, bool optimiseDirection) {
	int count = 0;
	int mainID = tileSet(y, x)->getComponent<Tile>().tileID;
	while (tileSet(y, x) && !tileSet(y, x)->hasGroup(antiGroup) &&
		   tileSet(y, x)->getComponent<Tile>().tileID == mainID) {
		y += optimiseDirection;
		x += !optimiseDirection;
		count++;
	}
	return count;
}

void Map::optimiseDeleter(int x, int y, int count, bool horizontal) {
	tileSet(y, x) = nullptr;
	for (int i = 1; i < count; i++) {
		sceneManager.getCurrentScene()->removeEntityFromScene(
			tileSet(y + i * !horizontal, x + i * horizontal)
		);
		tileSet(y + i * !horizontal, x + i * horizontal) = nullptr;
	}
}

void Map::optimiseMap() {
	for (int y = 0; y < tileSet.height(); y++) {
		for (int x = 0; x < tileSet.width(); x++) {
			if (!tileSet(y, x)) continue;
			bool horizontal = true;
			int count = optimiseHelper(x, y, PELLETS, false);
			if (!count) {
				tileSet(y, x) = nullptr;
				continue;
			}
			if (count == 1) {
				count = optimiseHelper(x, y, PELLETS, true);
				horizontal = false;
			}
			SDL_Rect tileRect = tileSet(y, x)->getComponent<Tile>().tileRect;

			tileSet(y, x)->getComponent<Tile>().resizeTile(
				tileRect.w + tileRect.w * (count - 1) * horizontal,
				tileRect.h + tileRect.h * (count - 1) * !horizontal
			);
			optimiseDeleter(x, y, count, horizontal);
		}
	}
}

void Map::loadMap() {
	int pixelVal;
	int xpos, ypos;

	for (int x = 0; x < img.width(); x++) {
		for (int y = 0; y < img.height(); y++) {
			pixelVal = colourReference(img(y, x));
			if (!pixelVal) continue;
			xpos = x * 32 + MAP_PADDING.x;
			ypos = y * 32 + MAP_PADDING.y;

			addTile(pixelVal, xpos, ypos);
			if (x == img.width() - 1) continue;

			xpos += (img.width() - x) * 64 - 64;
			addTile(pixelVal, xpos, ypos);
		}
	}
	optimiseMap();
}

void Map::reloadMap() {
	spawners.clear();
	pelletCount = 0;

	init();
	drawMap();
	loadMap();
}
