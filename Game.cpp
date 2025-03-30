#include "Game.h"
#include "Controller.h"
#include "Counters.h"
#include "GameplayScene.h"
#include "Map.h"
#include "MouseTracker.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include <SDL2/SDL_mixer.h>

Manager manager;
SceneManager sceneManager = SceneManager();

Game::Game() : mouse(manager.addEntity(MOUSE_TAG)) {}

Game::~Game() {}

TTF_Font* TextureManager::font;

float Game::deltaTime;
float Game::timeScale = 1.0f;

SDL_Point Game::mouseCoords;
bool Game::mouseButtonPressed = false;

bool Game::isPaused;

bool MouseTracker::isPressed;

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

std::vector<Entity*>& colliders(manager.getGroupMembers(COLLIDERS));
std::vector<Entity*>& tiles(manager.getGroupMembers(MAP));
std::vector<Entity*>& players(manager.getGroupMembers(PACMAN));
std::vector<Entity*>& ghosts(manager.getGroupMembers(GHOSTS));
std::vector<Entity*>& pellets(manager.getGroupMembers(PELLETS));
std::vector<Entity*>& ghostSpawns(manager.getGroupMembers(GHOST_BAR));

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

	// SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		std::cout << "Renderer created\n";
	}

	if (TTF_Init()) {
		std::cout << "TTF system failed to load, error: " << TTF_GetError() << '\n';
		return;
	}
	std::cout << "TTF system loaded succesfully\n";

	if (Mix_Init(MIX_INIT_WAVPACK)) { // set to filetype
		std::cout << "Mixer failed to initialise, error: " << Mix_GetError() << '\n';
		return;
	}
	std::cout << "Mixer initialised\n";

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
	// Mix_Music* audio = Mix_LoadMUS("./audio/audio.wav");
	// Mix_PlayMusic(audio, 0);
	// Mix_PauseMusic();

	mouse.enable();
	mouse.addComponent<MouseTracker>();
	TextureManager::font = TTF_OpenFont("./fonts/VCR_OSD_MONO.ttf", 32);
	isRunning = true;

	GameplayScene* gameScene = new GameplayScene();
	sceneManager.addScene(gameScene);
	sceneManager.loadScene(gameScene->buildIndex);
	gameScene = nullptr;

	// #include <TestScene.h>
	// 	TestScene* testScene = new TestScene();
	// 	sceneManager.addScene(testScene);
}

// function to handle game events
void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
		break;
	case SDL_MOUSEBUTTONDOWN:
		mouseButtonPressed = true;
		break;
	case SDL_MOUSEBUTTONUP:
		mouseButtonPressed = false;
		break;
	default:
		break;
	}
	sceneManager.callSceneEvents(event);
}

// update is called every frame. includes game logic
void Game::update() {
	manager.update();
	sceneManager.updateScene();
}

// render sprites to screen
void Game::render() {
	SDL_RenderClear(renderer);
	sceneManager.drawScene();
	SDL_RenderPresent(renderer);
}

void Game::ghostSpawn() {
	return;
}

// clean resources on game quitting
void Game::clean() {
	TTF_CloseFont(TextureManager::font);

	manager.destroyAll();

	Mix_HaltChannel(-1);
	Mix_HaltMusic();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	Mix_Quit();
	TTF_Quit();
	SDL_Quit();

	std::cout << "\nGame cleaned\n";
}

const bool Game::getPaused() {
	return isPaused;
}

void Game::setPause(bool pause) {
	isPaused = pause;
	timeScale = pause ? 0.0 : 1.0;
}
