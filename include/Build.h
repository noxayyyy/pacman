/**
 * @file Build.h
 * @brief Defines structures for procedurally generating the game map layout.
 */

#pragma once

#include "UserConstants.h"
#include <algorithm>
#include <vector>

/**
 * @brief Represents a single "digger" agent in the procedural map generation algorithm.
 * @details A Builder moves around a grid, carving out paths according to a set of rules.
 */
struct Builder {
public:
	/**
	 * @brief The four cardinal directions of movement.
	 */
	enum Direction { UP, DOWN, LEFT, RIGHT, NONE };

	Builder();
	~Builder();

	/**
	 * @brief Randomly determines if the builder should consider changing direction.
	 */
	void updateChance();

	/**
	 * @brief Determines if the builder *must* change direction due to map boundaries or step
	 * limits.
	 */
	void updateForceChange();

	/**
	 * @brief Assigns a new, valid direction to the builder if a change is forced.
	 */
	void assignDirection();

	/**
	 * @brief Updates the builder's active status based on the tiles it encounters.
	 * @param currBlock The character representing the current tile type.
	 * @param prevBlock The character representing the previous tile type.
	 * @return True if the builder just moved from a non-path to a path tile.
	 */
	bool updateActivity(char currBlock, char prevBlock);

	/**
	 * @brief Manually sets the active state of the builder.
	 * @param val The new active state.
	 */
	void setActive(bool val);

	/**
	 * @brief Checks if the builder is currently active.
	 * @return True if the builder is active.
	 */
	bool isActive();

	int x, y;          ///< Current grid coordinates.
	int currCount;     ///< Number of steps taken in the current direction.
	Direction currDir; ///< Current direction of movement.
	Direction prevDir; ///< Previous direction of movement.
	char currBlock;    ///< The character of the tile the builder is currently on.
	char prevBlock;    ///< The character of the tile the builder was previously on.
	bool forceChange;  ///< True if the builder must change direction.
	bool chanceChange; ///< True if the builder might randomly change direction.

private:
	bool active;
};

/**
 * @brief Manages a collection of Builder agents to generate a map.
 */
struct BuilderSpawner {
public:
	BuilderSpawner();
	~BuilderSpawner();

	/**
	 * @brief Updates the coordinates of all active builders based on their current direction.
	 */
	void moveBuilders();

	/**
	 * @brief Updates the internal state of all builders (e.g., direction changes).
	 */
	void updateBuilders();

	/**
	 * @brief Checks if any builder in the collection is still active.
	 * @return True if at least one builder is active.
	 */
	bool isActive();

	/**
	 * @brief Clears the collection of builders.
	 */
	void clear();

	int x, y;
	std::vector<Builder> builders;
};
