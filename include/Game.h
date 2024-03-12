#ifndef Game_h
#define Game_h

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <Vector2D.h>

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
		GHOST_BAR,
		PELLETS,
		COLLIDERS,
	};

	static std::unordered_map<SDL_Keycode, bool> KeyStates;
	static float deltaTime;
	static SDL_Event event;
	static SDL_Renderer* renderer;

	// declare game functions in class
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	static void collisionResponse(Vector2D oldVel);
	void collisionResponse();
	void checkCollisions();
	void ghostSpawn();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }

private:
	int count = 0;
	bool isRunning;
	SDL_Window* window;
	Vector2D lastVel;
};

#endif // !Game_hpp
