#pragma once

#include <Game.h>
#include <BuilderSpawner.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <utility>
#include <vector>
#include <unordered_map>

class Map {
public:
	Map();
	~Map();

	void init();

	int colourReference(std::string colour);
	void DrawMap();
	void LoadMap();
	void updateImg(Builder* builder, bool killPrevBlock);
	void addWalls(int x, int y);
	void addTile(int id, int x, int y);

private:
	static const int spawnerCount = 2;
	std::vector<std::vector<std::string>> img = std::vector(22, std::vector<std::string>(20, ""));
	std::unordered_map<std::string, int> colourMap;
};
