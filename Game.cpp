#include <Game.h>
#include <TextureManager.h>
#include <Map.h>
#include <Components.h>
#include <Controller.h>
#include <Vector2D.h>
#include <Collision.h>

Game::Game() {}
Game::~Game() {}

float Game::deltaTime;
Vector2D lastVel;
SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
Map* map;
Manager manager;
Controller* controller;
std::unordered_map<SDL_Keycode, bool> Game::Keys {
	{ SDLK_w, false }, { SDLK_s, false },
	{ SDLK_a, false }, { SDLK_d, false },
};

auto& pacman(manager.addEntity());
Transform* pacmanPos;
Collider* pacmanColl;

// game initialisation function
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystem Initialised\n";
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) std::cout << "Window created\n";
		SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) std::cout << "Renderer created\n";
		isRunning = true;
	} else isRunning = false;
	
	map = new Map();
	map->init();
	map->DrawMap();
	map->LoadMap();

	// ECS implementation

	pacman.addComponent<Transform>(65.0f, 33.0f);
	pacman.addComponent<Sprites>("C:/GameDev/sprites/pacman-ghosts-red_00.png");
	pacman.addComponent<Collider>("pacman");
	controller = new Controller(&pacman);
	pacman.addGroup(PACMAN);
	pacmanPos = &pacman.getComponent<Transform>();
	pacmanColl = &pacman.getComponent<Collider>();
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

auto& colliders(manager.getGroupMembers(Game::COLLIDERS));
auto& tiles(manager.getGroupMembers(Game::MAP));
auto& players(manager.getGroupMembers(Game::PACMAN));
// auto& ghosts(manager.getGroupMembers(Game::GHOSTS));
// auto& pellets(manager.getGroupMembers(Game::PELLETS));

void Game::collisionResponse(Vector2D oldVel) {
	for (auto& memColl : colliders) {
		if (memColl->getComponent<Collider>().tag != "wall") continue;
		Collider coll = memColl->getComponent<Collider>();
		if (Collision::AABBvel(*pacmanColl, coll)) {
			pacmanPos->vel.x = oldVel.x;
			pacmanPos->vel.y = oldVel.y;
			// coll.entity->getComponent<Sprites>().setTex("C:/GameDev/sprites/ghost_bar.png");
			break;
		}
	}
}

void Game::collisionResponse() {
	for (auto& memColl : colliders) {
		if (memColl->getComponent<Collider>().tag != "wall") continue;
		Collider coll = memColl->getComponent<Collider>();
		if (Collision::AABBvel(*pacmanColl, coll)) {
			pacmanPos->vel.x = pacmanPos->vel.y = 0.0f;
			// coll.entity->getComponent<Sprites>().setTex("C:/GameDev/sprites/ghost_bar.png");
			break;
		}
	}
}

// update is called every frame. includes game logic
void Game::update() {
	manager.refresh();
	manager.update();
	controller->updateVel();
	collisionResponse();
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
