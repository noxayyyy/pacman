/**
 * @file GameplayScene.h
 * @brief Defines the main scene for the Pac-Man game.
 */

#include "Animator.h"
#include "Constants.h"
#include "Controller.h"
#include "Game.h"
#include "Map.h"
#include "Scene.h"
#include "SceneManager.h"

extern Manager manager;
extern SceneManager sceneManager;

extern std::vector<Entity*> colliders;
extern std::vector<Entity*> tiles;
extern std::vector<Entity*> players;
extern std::vector<Entity*> ghosts;
extern std::vector<Entity*> pellets;
extern std::vector<Entity*> ghostSpawns;

/**
 * @brief The main scene that orchestrates the core gameplay loop.
 * @details This class is responsible for initializing the player, map, UI, and handling game logic.
 */
struct GameplayScene : public Scene {
public:
	GameplayScene();
	~GameplayScene() override;

	/**
	 * @brief Initializes all game elements: Pac-Man, the map, and UI components.
	 */
	void init() override;
	/**
	 * @brief Contains the main game logic that runs each frame, such as checking win conditions.
	 */
	void update() override;
	/**
	 * @brief Resets the level by reloading the map and resetting the player's position.
	 */
	void reload() override;
	/**
	 * @brief Reloads only the UI state, for use when unpausing.
	 */
	void reloadWithState() override;
	/**
	 * @brief Handles player input events for controlling Pac-Man.
	 * @param event The SDL_Event to process.
	 */
	void handleEvents(SDL_Event& event) override;
	/**
	 * @brief Draws all visible game elements in the correct order.
	 */
	void draw() override;

private:
	Entity& pacman;

	int* pointVal;
	int pelletCount;

	Transform* pacmanPos;
	Collider* pacmanColl;
	Controller* controller;

	std::shared_ptr<Map> map;

	void pacmanInit();
	void mapInit();
};
