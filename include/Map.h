#pragma once

#include <cstdlib>
#include <ctime>
#include <vector>
#include <unordered_map>
#include <csignal>
#include <Game.h>
#include <Tile.h>
#include <Build.h>
#include <Collider.h>

class Map {
public:
	struct MapArray {
		std::vector<char> arr;
		MapArray(char c) {
			arr = std::vector<char>(MAP_WIDTH * MAP_HEIGHT, c);
		}
		MapArray() {
			arr = std::vector<char>(MAP_WIDTH * MAP_HEIGHT);
		}
		~MapArray() = default;

		void clear(char c) {
			arr.clear();
			arr = std::vector<char>(MAP_WIDTH * MAP_HEIGHT, c);
		}

		inline
		char& operator() (int y, int x) {
			if (y >= MAP_HEIGHT || y < 0) {
				throw SIGSEGV;
			}
			if (x >= MAP_WIDTH || x < 0) {
				throw SIGSEGV;
			}
			return arr[y * MAP_WIDTH + x];
		}
		inline
		const char& operator() (int y, int x) const {
			if (y >= MAP_HEIGHT || y < 0) {
				throw SIGSEGV;
			}
			if (x >= MAP_WIDTH || x < 0) {
				throw SIGSEGV;
			}
			return arr[y * MAP_WIDTH + x];
		}
		inline
		const char& operator[] (int i) const {
			if (i >= MAP_HEIGHT * MAP_WIDTH) {
				throw SIGSEGV;
			}
			return arr[i];
		}
		inline
		char& operator[] (int i) {
			if (i >= MAP_HEIGHT * MAP_WIDTH) {
				throw SIGSEGV;
			}
			return arr[i];
		}

		int width() {
			return MAP_WIDTH;
		}
		int height() {
			return MAP_HEIGHT;
		}
	};

	static const int PADDING_X = 32; // 32
	static const int PADDING_Y = 0; // 64
	static const int MAP_WIDTH = 20; // 20
	static const int MAP_HEIGHT = 24; // 22

	Map();
	~Map();

	void init();

	int colourReference(char colour);
	void DrawMap();
	void LoadMap();
	void updateImg(BuilderSpawner& spawner, std::vector<bool> killPrevBlock);
	void addWalls(int x, int y);
	void addTile(int id, int x, int y);
	void addPassthrough();
	void addSpawnBox();

	void reloadMap();

private:
	static const char path = 'p';
	static const char blank = 'n';
	static const char wall = 'w';
	static const char ghostBar = 'g';
	static const char ghostSpawn = 's';
	static const int spawnerCount = 2;
	std::unordered_map<char, int> colourMap;
	MapArray img;
};
