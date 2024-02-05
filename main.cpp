#define SDL_MAIN_HANDLED
#include <Game.h>

Game* game = nullptr;

int main(int argc, char** argv) {
	// frame rate
	const int FPS = 60;
	// max time a frame is supposed to last for
	const float frameDelay = 1.0f / (float)FPS;

	Uint32 frameStart;
	game = new Game();
	
	game->init("NoxEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);
	
	while (game->running()) {
		// get time since SDL initialisation
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		// get time taken to handle events, update frame, and render frame
		Game::deltaTime = (float)(SDL_GetTicks() - frameStart) / 1000.0f;
		// std::cout << "deltaTime: " << Game::deltaTime << '\n';
		// if fps is greater than 60, increase delay to limit frames
		if (Game::deltaTime < frameDelay) {
			SDL_Delay((frameDelay - Game::deltaTime) * 1000);
			Game::deltaTime = frameDelay;
		}
	}
	game->clean();
	
	return 0;
}