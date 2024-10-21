#include <Game.h>
#include <Scene.h>

class TestScene : public Scene {
public:
	TestScene() : Scene("Test", 1, false, true, 1) { }

	void init() override { }
	void update() override { }
	void reload() override { }
	void handleEvents(SDL_Event& event) override { }
	void draw() override { }
};
