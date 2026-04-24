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
	/**
	 * @brief A 2D array container with bounds checking for map data.
	 * @tparam T The data type to be stored in the grid.
	 */
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

		/**
		 * @brief Clears the array and fills it with a new entry.
		 * @param entry The value to fill the array with.
		 */
		void clear(T entry) {
			arr.clear();
			arr = std::vector<T>(w * h, entry);
		}

		/**
		 * @brief Accesses an element using 2D coordinates.
		 * @param y The row index.
		 * @param x The column index.
		 * @return A reference to the element.
		 */
		inline T& operator()(int y, int x) {
			if (y >= h || y < 0) {
				throw std::runtime_error("Map oob access.");
			}
			if (x >= w || x < 0) {
				throw std::runtime_error("Map oob access.");
			}
			return arr[y * w + x];
		}

		/**
		 * @brief Accesses an element using 2D coordinates.
		 * @param y The row index.
		 * @param x The column index.
		 * @return A reference to the element.
		 */
		inline const T& operator()(int y, int x) const {
			if (y >= h || y < 0) {
				throw std::runtime_error("Map oob access.");
			}
			if (x >= w || x < 0) {
				throw std::runtime_error("Map oob access.");
			}
			return arr[y * w + x];
		}

		/**
		 * @brief Accesses an element using a 1D index.
		 * @param i The linear index.
		 * @return A reference to the element.
		 */
		inline const T& operator[](int i) const {
			if (i >= h * w) {
				throw std::runtime_error("Map oob access.");
			}
			return arr[i];
		}

		/**
		 * @brief Accesses an element using a 1D index.
		 * @param i The linear index.
		 * @return A reference to the element.
		 */
		inline T& operator[](int i) {
			if (i >= h * w) {
				throw std::runtime_error("Map oob access.");
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

	/**
	 * @brief Initializes the map generation process.
	 */
	void init();

	/**
	 * @brief Helper to get a tile ID from a character representation.
	 * @param colour The character representing the tile type.
	 * @return The integer ID of the tile.
	 */
	int colourReference(char colour);
	/**
	 * @brief Procedurally generates the map layout using Builder agents.
	 */
	void drawMap();
	/**
	 * @brief Creates entities (Tiles) based on the generated map layout.
	 */
	void loadMap();
	/**
	 * @brief Clears and re-loads the map entities.
	 */
	void reloadMap();
	/**
	 * @brief Updates the internal character map based on builder positions.
	 * @param spawner The BuilderSpawner managing the generation agents.
	 * @param killPrevBlock Flags for tile-overwriting logic.
	 */
	void updateImg(BuilderSpawner& spawner, std::vector<bool> killPrevBlock);
	/**
	 * @brief Adds wall tiles around a specified path tile.
	 * @param x The grid x-coordinate of the path tile.
	 * @param y The grid y-coordinate of the path tile.
	 */
	void addWalls(int x, int y);
	/**
	 * @brief Creates a single tile entity at a specific location.
	 * @param id The type ID of the tile.
	 * @param x The grid x-coordinate.
	 * @param y The grid y-coordinate.
	 */
	void addTile(int id, int x, int y);
	/**
	 * @brief Post-processing pass to add colliders to all wall tiles.
	 */
	void addCollPass();
	/**
	 * @brief Post-processing pass to fill in a row with tiles.
	 * @param y The row index to process.
	 */
	void addRowPass(int y);
	/**
	 * @brief Adds the central ghost spawn box to the map.
	 */
	void addSpawnBox();
	/**
	 * @brief Optimizes the map by merging adjacent wall colliders into larger ones.
	 */
	void optimiseMap();
	int optimiseHelper(int x, int y, GroupID antiGroup, bool optimiseDirection = false);
	void optimiseDeleter(int x, int y, int count, bool horizontal = true);

	/**
	 * @brief Gets the total number of pellets on the map.
	 * @return The pellet count.
	 */
	const int getPelletCount() const {
		return pelletCount;
	}

private:
	static int pelletCount;
	std::unordered_map<char, int> colourMap;
	MapArray<char> img;
	MapArray<Entity*> tileSet;
};
