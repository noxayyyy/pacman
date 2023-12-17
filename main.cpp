#define SDL_MAIN_HANDLED
#include <Game.h>

Game* game = nullptr;

int main(int argc, char** argv) {
	// frame rate
	const int FPS = 60;
	// max time a frame is supposed to last for
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	game = new Game();
	
	game->init("NoxEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);
	
	while (game->running()) {
		// get time since SDL initialisation
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		// get time taken to handle events, update frame, and render frame
		frameTime = SDL_GetTicks() - frameStart;
		// if fps is greater than 60, increase delay to limit frames
		if (frameTime < frameDelay) SDL_Delay(frameDelay - frameTime);
	}
	game->clean();
	
	return 0;
}