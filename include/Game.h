#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <Vector2D.h>

class Game {
public:
	// Game constructor
	Game();
	// Game deconstructor
	~Game();

	enum GroupLabels : std::size_t {
		MAP,
		PACMAN,
		GHOSTS,
		GHOST_BAR,
		PELLETS,
		COLLIDERS,
	};

	static const int PACMAN_SPAWN[2];
	static std::unordered_map<SDL_Keycode, bool> KeyStates;
	static float deltaTime;
	static SDL_Event event;
	static SDL_Renderer* renderer;

	// declare game functions in class
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void ghostSpawn();
	void update();
	void render();
	void clean();
	bool running() { 
		return isRunning; 
	}

private:
	bool isRunning;
	SDL_Window* window;
	Vector2D lastVel;
};
