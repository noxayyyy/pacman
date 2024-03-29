#pragma once

#include <Game.h>
#include <BuilderSpawner.h>
#include <Tile.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <utility>
#include <vector>
#include <unordered_map>

class Map {
public:
	static const int PADDING_X = 32;
	static const int PADDING_Y = 64;

	Map();
	~Map();

	void init();

	int colourReference(std::string colour);
	void DrawMap();
	void LoadMap();
	void updateImg(Builder* builder, bool killPrevBlock);
	void addWalls(int x, int y);
	void addTile(int id, int x, int y);
	void addPassthrough();
	bool checkTurn(Tile* tile);

private:
	static const int spawnerCount = 2;
	static std::vector<std::vector<std::string>> img;
	std::unordered_map<std::string, int> colourMap;
};
