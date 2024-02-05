#ifndef Game_h
#define Game_h

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

class Collider;

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
		PELLETS,
		COLLIDERS,
	};

	static float deltaTime;
	static SDL_Event event;
	static SDL_Renderer* renderer;

	// declare game functions in class
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void collisionResponse();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }

private:
	int count = 0;
	bool isRunning;
	SDL_Window* window;
};

#endif // !Game_hpp
