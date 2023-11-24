#include "Game.hpp"

Game* game = nullptr;

int main(int args, char* argv[]) {
	game = new Game();
	
	game->init("NoxEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	
	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();
	
	return 0;
}