#include <Map.h>
#include <ECS.h>
#include <Components.h>

extern Manager manager;

BuilderSpawner* firstSpawner;
BuilderSpawner* secondSpawner;
std::vector<BuilderSpawner*> spawners;

static const std::string pathStr = "255 255 255";
static const std::string blankStr = "0 0 0";
static const std::string wallStr = "255 0 0";
static const std::string ghostBarStr = "0 0 255";

Map::Map() {
	firstSpawner = new BuilderSpawner();
	secondSpawner = new BuilderSpawner();
}

Map::~Map() {}

void Map::init() {
	firstSpawner->init();
	secondSpawner->init();
	spawners.push_back(firstSpawner);
	spawners.push_back(secondSpawner);
	colourMap[pathStr] = 0;
	colourMap[wallStr] = 1;
	colourMap[ghostBarStr] = 2;
	colourMap[blankStr] = 3;
}

bool checkRepeat(int xpos, int ypos) {
	for (auto& spawn : spawners) if (abs(spawn->x - xpos) <= 1 && abs(spawn->y - ypos) <= 1) return true;
	return false;
}

void Map::addWalls(int x, int y) {
	for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++) 
		if (img[y + i][x + j] != pathStr) img[y + i][x + j] = wallStr;
}

void Map::updateImg(Builder* builder, bool killPrevBlock) {
	img[builder->y][builder->x] = pathStr;

	switch (builder->currDir) {
	case Builder::UP:
		img[builder->y + 1][builder->x] = pathStr;
		break;
	case Builder::DOWN:
		img[builder->y - 1][builder->x] = pathStr;
		break;
	case Builder::LEFT:
		img[builder->y][builder->x + 1] = pathStr;
		break;
	case Builder::RIGHT:
		img[builder->y][builder->x - 1] = pathStr;
		break;
	default:
		break;
	}
	if (killPrevBlock) img[builder->y][builder->x] = blankStr;
}

bool checkSpawnerActivities(std::vector<BuilderSpawner*> spawners) {
	for (auto& spawn : spawners) if (spawn->firstBuilder->isActive() || spawn->secondBuilder->isActive() 
		|| spawn->thirdBuilder->isActive()) return true;
	return false;
}

void Map::DrawMap() {
	srand(time(0));

	spawners[0]->x = spawners[1]->x = 10;
	spawners[0]->y = 1; spawners[1]->y = 19;

	for (auto& spawn : spawners) {
		spawn->firstBuilder->x = spawn->x + 8;
		spawn->secondBuilder->x = spawn->x - 8;
		spawn->thirdBuilder->x = spawn->x;

		spawn->firstBuilder->y = spawn->secondBuilder->y = spawn->y;
	}

	spawners[0]->thirdBuilder->y = spawners[0]->y + 2;
	spawners[1]->thirdBuilder->y = spawners[1]->y - 2;

	for (int i = 0; i < 3; i++) {
		spawners[0]->builders[i]->currDir = Builder::DOWN;
		spawners[1]->builders[i]->currDir = Builder::UP;
	}

	for (int y = 0; y < 22; y++) for (int x = 0; x < 20; x++) img[y][x] = blankStr;

	for (int i = spawners[0]->x - 8; i < spawners[0]->x + 9; i++) {
		img[spawners[0]->y][i] = pathStr;
		img[spawners[1]->y][i] = pathStr;
	}
	for (int i = 0; i < 3; i++) {
		img[spawners[0]->y + i][spawners[0]->x] = pathStr;
		img[spawners[1]->y - i][spawners[0]->x] = pathStr;
	}
	
	std::vector<std::vector<bool>> killPrevBlock = { { false, false, false }, { false, false, false } };

	while (checkSpawnerActivities(spawners)) {
		for (int i = 0; i < spawnerCount; i++) {
			spawners[i]->moveBuilders();
			killPrevBlock[i] = spawners[i]->updateActivity(img);
			updateImg(spawners[i]->firstBuilder, killPrevBlock[i][0]);
			updateImg(spawners[i]->secondBuilder, killPrevBlock[i][1]);
			updateImg(spawners[i]->thirdBuilder, killPrevBlock[i][2]);
		}
		
		for (auto& spawn : spawners) for (auto& build : spawn->builders) {
			build->updateChance();
			build->updateForceChange();
		}
		for (auto& spawn : spawners) for (auto& build : spawn->builders) build->assignDirection();
	}

	for (int y = 0; y < 22; y++) for (int x = 0; x < 20; x++) {
		if (img[y][x] != pathStr) continue;
		addWalls(x, y);
	}

	for (int i = 0; i < 4; i++) {
		int x = rand() % 18 + 1;
		while (img[x][18] != pathStr || img[x - 1][19] == pathStr || 
			img[x + 1][19] == pathStr) x = rand() % 18 + 1;
		img[x][19] = pathStr;
	}
}

int Map::colourReference(std::string colour) {
	if (colourMap.find(colour) != colourMap.end()) return colourMap[colour];
	return -1;
}

void Map::addTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<Tile>(x, y, 50, 50, id);
	switch (id) {
	case 0:
		tile.addComponent<Collider>("path");
		break;
	case 1:
		tile.addComponent<Collider>("wall");
		break;
	case 2:
		tile.addComponent<Collider>("ghostBar");
		break;
	default:
		tile.addComponent<Collider>("path");
		break;
	}
	tile.addGroup(Game::MAP);
	tile.addGroup(Game::COLLIDERS);
}

void Map::LoadMap() {
	int pixelVal;
	int xpos = 0, ypos = 0;
	for (int x = 0; x < img[0].size(); x++) for (int y = 0; y < img.size(); y++) {
		pixelVal = colourReference(img[y][x]);
		xpos = x * 32;
		ypos = y * 32;
		addTile(pixelVal, xpos, ypos);
		xpos += (img[0].size() - x) * 64 - 32;
		addTile(pixelVal, xpos, ypos);
	}
}