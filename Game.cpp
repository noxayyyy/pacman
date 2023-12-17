#include <Game.h>
#include <TextureManager.h>
#include <Map.h>
#include <Components.h>
#include <Vector2D.h>
#include <Collision.h>

Game::Game() {}
Game::~Game() {}

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
Map* map;
Manager manager;

auto& pacman(manager.addEntity());
Transform* pacmanPos;

// game initialisation function
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
	
	map = new Map();
	map->init();
	map->DrawMap();
	map->LoadMap();

	// ECS implementation

	pacman.addComponent<Transform>(64.0f, 32.0f);
	pacman.addComponent<Sprites>("C:/GameDev/sprites/pacman-ghosts-red_00.png");
	pacman.addComponent<Controller>();
	pacman.addComponent<Collider>("pacman");
	pacman.addGroup(PACMAN);
	pacmanPos = &pacman.getComponent<Transform>();
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
}

auto& colliders(manager.getGroupMembers(Game::COLLIDERS));
auto& tiles(manager.getGroupMembers(Game::MAP));
auto& players(manager.getGroupMembers(Game::PACMAN));
// auto& ghosts(manager.getGroupMembers(Game::GHOSTS));
// auto& pellets(manager.getGroupMembers(Game::PELLETS));

// update is called every frame. includes game logic
void Game::update() {
	SDL_Rect pacmanCol = pacman.getComponent<Collider>().collider;
	Vector2D posPacman = pacmanPos->pos;

	manager.refresh();
	manager.update();

	for (auto& memColl : colliders) {
		if (memColl->getComponent<Collider>().tag != "wall") continue;
		SDL_Rect coll = memColl->getComponent<Collider>().collider;
		/*if (Collision::AABB(pacmanCol, coll)) {
			pacmanPos->pos = posPacman;
		}*/
	}
}

// render sprites to screen
void Game::render() {
	SDL_RenderClear(renderer);
	// add shit to render
	for (auto& t : tiles) t->draw();
	// for (auto& p : pellets) p->draw();
	// for (auto& g : ghosts) g->draw();
	for (auto& p : players) p->draw();
	
	SDL_RenderPresent(renderer);
}

// clean resources on game quitting
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "\nGame cleaned\n";
}
