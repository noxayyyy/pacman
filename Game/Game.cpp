#include "Game.hpp"

Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystem Initialised\n";
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) std::cout << "Window created\n";
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) std::cout << "Renderer created\n";
		isRunning = true;
	} else isRunning = false;
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	std::cout << count << '\n';
	count++;
}

void Game::render() {
	SDL_RenderClear(renderer);
	// add shit to render
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned\n";
}
