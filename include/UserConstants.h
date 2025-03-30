#pragma once

#include "Constants.h"
#include <SDL2/SDL_rect.h>
#include <string>

// game
const std::string PACMAN_TAG = "pacman";
const SDL_Point PACMAN_SPAWN { 19, 1 };

// build
const int MAX_STEP = 3;

// map
const std::string PELLET_TAG = "pellet";
// const std::string WALL_TAG = "wall";
const SDL_Point MAP_PADDING { 32, 0 };
const SDL_Point MAP_SIZE { 20, 24 };
const char PATH = 'p';
const char BLANK = 'n';
const char WALL = 'w';
const char GHOST_BAR_CHAR = 'g';
const char GHOST_SPAWN = 's';
const int SPAWNER_COUNT = 2;

// points
const int VALUE_PER_PELLET = 10;
