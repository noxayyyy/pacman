#include <Game.h>
#include <TextureManager.h>
#include <Map.h>
#include <Controller.h>
#include <Vector2D.h>
#include <Collision.h>
#include <Counters.h>
#include <GameplayScene.cpp>
#include <SceneManager.h>

Game::Game() {}
Game::~Game() {}

float Game::deltaTime;
const int Game::PACMAN_SPAWN[2] = { 19, 1 };
SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

Manager manager = Manager();
SceneManager sceneManager;
GameplayScene* gameScene;
Controller* controller;

std::vector<Entity*>& colliders(manager.getGroupMembers(Game::COLLIDERS));
std::vector<Entity*>& tiles(manager.getGroupMembers(Game::MAP));
std::vector<Entity*>& players(manager.getGroupMembers(Game::PACMAN));
std::vector<Entity*>& ghosts(manager.getGroupMembers(Game::GHOSTS));
std::vector<Entity*>& pellets(manager.getGroupMembers(Game::PELLETS));
std::vector<Entity*>& ghostSpawns(manager.getGroupMembers(Game::GHOST_BAR));

std::unordered_map<SDL_Keycode, bool> Game::KeyStates {
	{ SDLK_w, false }, { SDLK_s, false },
	{ SDLK_a, false}, { SDLK_d, false },
};

// game initialisation function
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
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
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		std::cout << "Renderer created\n";
	}

	if (TTF_Init()) {
		std::cout << "TTF system failed to load, error: " << TTF_GetError() << '\n';
		return;
	}
	std::cout << "TTF system loaded succesfully\n";

	TextureManager::font = TTF_OpenFont("./fonts/VCR_OSD_MONO.ttf", 32);
	isRunning = true;
	
	gameScene = new GameplayScene();
	sceneManager.addScene(gameScene);
	sceneManager.loadScene(gameScene->buildIndex);
}

// function to handle game events
void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		controller->updateKeyDown(event.key.keysym.sym);
		break;	
	case SDL_KEYUP:
		controller->updateKeyUp(event.key.keysym.sym);
		break;
	default:
		break;
	}
}

// update is called every frame. includes game logic
void Game::update() {
	manager.update();
	sceneManager.getCurrentScene()->update();
}

// render sprites to screen
void Game::render() {
	SDL_RenderClear(renderer);
	sceneManager.getCurrentScene()->draw();
	SDL_RenderPresent(renderer);
}

void Game::ghostSpawn() {
	return;
}

// clean resources on game quitting
void Game::clean() {
	TTF_CloseFont(TextureManager::font);
	free(controller);
	free(gameScene);
	manager.destroyAll();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	std::cout << "\nGame cleaned\n";
}
