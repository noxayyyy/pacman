#include "Game.h"
#include "Scene.h"

extern Manager manager;

struct TestScene : public Scene {
public:
	TestScene() : Scene("Test", 1, true, true, 1) {}

	void init() override {}

	void update() override {}

	void reload() override {}

	void reloadWithState() override {}

	void handleEvents(SDL_Event& event) override {}

	void draw() override {}
};
