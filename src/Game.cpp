#include "../engine/include/Game.h"
#include "../engine/include/Controller.h"
#include "../engine/include/Counters.h"
#include "../engine/include/MouseTracker.h"
#include "../engine/include/SceneManager.h"
#include "../engine/include/TextureManager.h"
#include "../engine/include/Vector2D.h"
#include "../include/GameplayScene.h"
#include "../include/Map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#include <fcntl.h>

Manager manager;
SceneManager sceneManager = SceneManager();

float Game::deltaTime;
float Game::timeScale = 1.0f;

SDL_Point Game::mouseCoords;
bool Game::mouseButtonPressed = false;

bool Game::isPaused;

bool MouseTracker::isPressed;

SDL_Event Game::event;
SDL_Surface* Game::screen = nullptr;

char Game::btn_state[8];

std::vector<Entity*> colliders(manager.getGroupMembers(COLLIDERS));
std::vector<Entity*> tiles(manager.getGroupMembers(MAP));
std::vector<Entity*> players(manager.getGroupMembers(PACMAN));
std::vector<Entity*> ghosts(manager.getGroupMembers(GHOSTS));
std::vector<Entity*> pellets(manager.getGroupMembers(PELLETS));
std::vector<Entity*> ghostSpawns(manager.getGroupMembers(GHOST_BAR));

Game::Game() : mouse(manager.addEntity(MOUSE_TAG)) {
	fd = open("/dev/buttons", O_RDONLY | O_NONBLOCK);
	if (fd < 0) {
		perror("Controller: failed to open /dev/buttons\n");
	}
	memset(btn_state, '0', sizeof(btn_state));
}

Game::~Game() {
	if (fd >= 0) {
		close(fd);
	}
	clean();
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER)) {
		std::cout << "Subsystem failed to intialise, error: " << SDL_GetError() << '\n';
		isRunning = false;
		return;
	}
	std::cout << "Subsystem Initialised\n";

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (window) {
		std::cout << "Window created\n";
	}

	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	screen = SDL_GetWindowSurface(window);

	isRunning = true;

	GameplayScene* gameScene = new GameplayScene();
	sceneManager.addScene(gameScene);
	sceneManager.loadScene(gameScene->buildIndex);
	gameScene = nullptr;
}

void Game::handleEvents() {
	read(fd, btn_state, sizeof(btn_state));
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
	sceneManager.callSceneEvents(event);
}

void Game::update() {
	manager.update();
	sceneManager.updateScene();
}

void Game::render() {
	SDL_FillRect(screen, NULL, 0);
	sceneManager.drawScene();
	SDL_UpdateWindowSurface(window);
}

void Game::ghostSpawn() {
	return;
}

void Game::clean() {
	manager.destroyAll();

	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);

	SDL_Quit();
	std::cout << "\nGame cleaned\n";
}

bool Game::getPaused() {
	return isPaused;
}

void Game::setPause(bool pause) {
	isPaused = pause;
	timeScale = pause ? 0.0 : 1.0;
}

char Game::getBtnState(int idx) {
	return btn_state[idx];
}
