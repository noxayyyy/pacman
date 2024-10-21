#define SDL_MAIN_HANDLED
#include <Game.h>

Game* game = nullptr;

int main(int argc, char** argv) {
	// frame rate
	const int FPS_CAP = 60;
	bool frameLock = false;
	// max time a frame is supposed to last for
	const float FRAME_DELAY = 1.0f / (float)FPS_CAP;

	Uint32 frameStart;
	Uint32 frameTime;

	game = new Game();
	game->init("NoxEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, false);

	while (game->running()) {
		// get time since SDL initialisation
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		// get time taken to handle events, update frame, and render frame
		Game::deltaTime = (float)frameTime / 1000.0f;

		// if fps is greater than 60, increase delay to limit frames
		if (frameLock && Game::deltaTime < FRAME_DELAY) {
			SDL_Delay((FRAME_DELAY - Game::deltaTime) * 1000);
			Game::deltaTime = FRAME_DELAY;
		}
		Game::deltaTime *= Game::timeScale;
	}
	game->clean();
	
	return 0;
}
