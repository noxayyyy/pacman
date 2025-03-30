#pragma once

#include <SDL2/SDL_rect.h>
#include <string>

enum GroupLabels : std::size_t {
	MAP,
	PACMAN,
	GHOSTS,
	GHOST_BAR,
	PELLETS,
	COLLIDERS,
	BUTTONS,
};

// main
const int FPS_CAP = 60;
const float FRAME_DELAY = 1.0f / (float)FPS_CAP;

// ECS
const std::size_t MAX_COMPONENTS = 32;
const std::size_t MAX_GROUPS = 32;

// game
const SDL_Point WINDOW_SIZE { 1366, 768 };

// scene manager
const int MAX_SCENE_COUNT = 10;

// counters
const int SAMPLE_COUNT = 10;

// mouse
const std::string MOUSE_TAG = "mouse";

const std::string WALL_TAG = "wall";

// anim
static const char* ANIM_ENTRY = "animentry";
