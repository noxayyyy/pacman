#include <Game.h>
#include <SDL2/SDL_mixer.h>
#include <TextureManager.h>
#include <Map.h>
#include <Controller.h>
#include <Vector2D.h>
#include <Collision.h>
#include <Counters.h>
#include <GameplayScene.h>
#include <SceneManager.h>

#include <TestScene.h>

Game::Game() {}
Game::~Game() {}

TTF_Font* TextureManager::font;

float Game::deltaTime;
float Game::timeScale = 1.0f;

SDL_Rect Game::mouseRect = SDL_Rect();
bool Game::mouseButtonPressed = false;

bool Game::isPaused;

const int Game::PACMAN_SPAWN[2] = { 19, 1 };

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

Manager manager = Manager();
SceneManager sceneManager = SceneManager();
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

	TextureManager::font = TTF_OpenFont("./fonts/VCR_OSD_MONO.ttf", 32);
	isRunning = true;
	
	GameplayScene* gameScene = new GameplayScene();
	sceneManager.addScene(gameScene);
	sceneManager.loadScene(gameScene->buildIndex);
	gameScene = nullptr;

	TestScene* testScene = new TestScene();
	sceneManager.addScene(testScene);
}

// function to handle game events
void Game::handleEvents() {
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

	free(controller);
	controller = nullptr;

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
