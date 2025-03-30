#pragma once

#include "Constants.h"
#include "ECS.h"
#include "Vector2D.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_ttf.h>

class Game {
public:
	// Game constructor
	Game();
	// Game deconstructor
	~Game();

	static float deltaTime;
	static float timeScale;
	static SDL_Event event;
	static SDL_Renderer* renderer;
	static SDL_Point mouseCoords;
	static bool mouseButtonPressed;

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

	static void setPause(bool pause);
	static const bool getPaused();

private:
	bool isRunning;
	static bool isPaused;
	SDL_Window* window;
	Entity& mouse;
};
