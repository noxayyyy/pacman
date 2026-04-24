/**
 * @file TestScene.h
 * @brief Defines a blank scene for testing purposes.
 */

#include "Game.h"
#include "Scene.h"

extern Manager manager;

/**
 * @brief An empty scene implementation, useful for scaffolding or testing new features.
 */
struct TestScene : public Scene {
public:
	TestScene() : Scene("Test", 1, true, true, 1) {}

	/** @brief (Empty) */
	void init() override {}

	/** @brief (Empty) */
	void update() override {}

	/** @brief (Empty) */
	void reload() override {}

	/** @brief (Empty) */
	void reloadWithState() override {}

	/** @brief (Empty) */
	void handleEvents(SDL_Event& event) override {}

	/** @brief (Empty) */
	void draw() override {}
};
