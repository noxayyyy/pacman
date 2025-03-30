#pragma once

#include "Build.h"
#include "Collider.h"
#include "ECS.h"
#include "Game.h"
#include "Tile.h"
#include "UserConstants.h"
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <vector>

struct Map {
public:
	template<typename T>
	struct MapArray {
	private:
		std::vector<T> arr;
		int w;
		int h;

	public:
		MapArray(int w, int h) {
			arr = std::vector<T>(w * h);
			this->w = w;
			this->h = h;
		}

		MapArray(int w, int h, T entry) {
			arr = std::vector<T>(w * h, entry);
			this->w = w;
			this->h = h;
		}

		MapArray(T entry) {
			arr = std::vector<T>(MAP_SIZE.x * MAP_SIZE.y, entry);
			w = MAP_SIZE.x;
			h = MAP_SIZE.y;
		}

		MapArray() {
			arr = std::vector<T>(MAP_SIZE.x * MAP_SIZE.y);
			w = MAP_SIZE.x;
			h = MAP_SIZE.y;
		}

		~MapArray() = default;

		void clear(T entry) {
			arr.clear();
			arr = std::vector<T>(w * h, entry);
		}

		inline T& operator()(int y, int x) {
			if (y >= h || y < 0) {
				throw SIGSEGV;
			}
			if (x >= w || x < 0) {
				throw SIGSEGV;
			}
			return arr[y * w + x];
		}

		inline const T& operator()(int y, int x) const {
			if (y >= h || y < 0) {
				throw SIGSEGV;
			}
			if (x >= w || x < 0) {
				throw SIGSEGV;
			}
			return arr[y * w + x];
		}

		inline const T& operator[](int i) const {
			if (i >= h * w) {
				throw SIGSEGV;
			}
			return arr[i];
		}

		inline T& operator[](int i) {
			if (i >= h * w) {
				throw SIGSEGV;
			}
			return arr[i];
		}

		inline void operator=(MapArray<T> other) {
			arr.clear();
			w = other.w;
			h = other.h;
			arr = std::vector<T>(w * h);
			for (int y = 0; y < h; y++) {
				for (int x = 0; x < w; x++) {
					(*this)(y, x) = other(y, x);
				}
			}
		}

		int width() {
			return w;
		}

		int height() {
			return h;
		}
	};

	Map();
	~Map();

	void init();

	int colourReference(char colour);
	void drawMap();
	void loadMap();
	void reloadMap();
	void updateImg(BuilderSpawner& spawner, std::vector<bool> killPrevBlock);
	void addWalls(int x, int y);
	void addTile(int id, int x, int y);
	void addCollPass();
	void addRowPass(int y);
	void addSpawnBox();
	void optimiseMap();
	int optimiseHelper(int x, int y, GroupID antiGroup, bool optimiseDirection = false);
	void optimiseDeleter(int x, int y, int count, bool horizontal = true);

	const int getPelletCount() const {
		return pelletCount;
	}

private:
	static int pelletCount;
	std::unordered_map<char, int> colourMap;
	MapArray<char> img;
	MapArray<Entity*> tileSet;
};
