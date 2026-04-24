/**
 * @file UserConstants.h
 * @brief Defines game-specific constants, separate from the core engine constants.
 */

#pragma once

#include "Constants.h"
#include <SDL2/SDL_rect.h>
#include <string>

// game
const std::string PACMAN_TAG = "pacman"; ///< The entity ID tag for the player.
const SDL_Point PACMAN_SPAWN { 19, 1 };  ///< The initial grid coordinates for Pac-Man.

// build
const int MAX_STEP = 3; ///< Max steps a map Builder can take in one direction.

// map
const std::string PELLET_TAG = "pellet"; ///< The collider tag for pellets.
const SDL_Point MAP_PADDING { 32, 0 };   ///< The pixel padding for rendering the map on screen.
const SDL_Point MAP_SIZE { 20, 24 };     ///< The dimensions of the map grid.
const char PATH = 'p';                   ///< Character representation for a path tile.
const char BLANK = 'n';                  ///< Character representation for an empty tile.
const char WALL = 'w';                   ///< Character representation for a wall tile.
const char GHOST_BAR_CHAR = 'g';         ///< Character representation for the ghost bar tile.
const char GHOST_SPAWN = 's';            ///< Character representation for a ghost spawn point.
const int SPAWNER_COUNT = 2;             ///< Number of BuilderSpawners to use for map generation.

// points
const int VALUE_PER_PELLET = 10; ///< The score awarded for collecting one pellet.
