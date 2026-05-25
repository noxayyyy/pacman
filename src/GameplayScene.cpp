#include "GameplayScene.h"
#include "UserConstants.h"

extern Manager manager;
extern SceneManager sceneManager;

extern std::vector<Entity*> colliders;
extern std::vector<Entity*> tiles;
extern std::vector<Entity*> players;
extern std::vector<Entity*> ghosts;
extern std::vector<Entity*> pellets;
extern std::vector<Entity*> ghostSpawns;

// TODO: Buttons causing crash
GameplayScene::GameplayScene()
	: Scene("Gameplay", 0, false, true, 0), pacman(manager.addEntity(PACMAN_TAG)) {}

// fps(manager.addEntity("fps")), points(manager.addEntity("points")),
// pauseButton(manager.addEntity("pauseButton")),
// reloadButton(manager.addEntity("reloadButton"))

GameplayScene::~GameplayScene() {
	clearScene();

	delete controller;
	delete pointVal;
	controller = nullptr;
	pointVal = nullptr;

	pacmanPos = nullptr;
	pacmanColl = nullptr;

	map.reset();
}

void GameplayScene::init() {
	pacmanInit();
	mapInit();

	pelletCount = map->getPelletCount();

	// fps.addComponent<FPS>("FPS");
	// pointVal = &points.addComponent<Points>("POINTS").value;
	pointVal = new int(0);
	// pauseButton.addComponent<Button>("PAUSE", 400, 222, 64, 32, []() {
	// 	Game::setPause(!Game::getPaused());
	// 	// sceneManager.loadNextScene();
	// });
	// reloadButton.addComponent<Button>("RELOAD", 8, 222, 64, 32, []() {
	// 	sceneManager.reloadScene();
	// });

	// addEntityToScene(fps);
	// addEntityToScene(points);
	// addEntityToScene(pauseButton);
	// addEntityToScene(reloadButton);

	colliders = manager.getGroupMembers(COLLIDERS);
	players = manager.getGroupMembers(PACMAN);
	tiles = manager.getGroupMembers(MAP);
	pellets = manager.getGroupMembers(PELLETS);

	enableScene();
	manager.refresh();
}

void GameplayScene::update() {
	// collisionResponse(controller->getLastVel());
	// checkCollisions();

	// points.update();
	// fps.update();
	// pauseButton.update();
	// reloadButton.update();

	if (pelletCount <= *pointVal / VALUE_PER_PELLET) {
		reload();
		pelletCount += map->getPelletCount();
	}
}

void GameplayScene::reload() {
	pacman.reload();

	for (auto it = tiles.begin(); it != tiles.end(); it++) {
		(*it)->disable();
		removeEntityFromScene(*it);
	}
	for (auto it = pellets.begin(); it != pellets.end(); it++) {
		(*it)->disable();
		removeEntityFromScene(*it);
	}
	manager.refresh();
	map->reloadMap();

	colliders = manager.getGroupMembers(COLLIDERS);
	tiles = manager.getGroupMembers(MAP);
	pellets = manager.getGroupMembers(PELLETS);

	enableScene();
	manager.refresh();
}

void GameplayScene::reloadWithState() {
	// pauseButton.reload();
}

void GameplayScene::handleEvents(SDL_Event& event) {
	switch (event.type) {
	case SDL_KEYDOWN:
		controller->updateKeyDown(event.key.keysym.sym);
		break;
	case SDL_KEYUP:
		controller->updateKeyUp(event.key.keysym.sym);
		break;
	default:
		break;
	}
	if (Game::getBtnState(1) == '1') {
		Game::setPause(!Game::getPaused());
	}
	if (Game::getBtnState(2) == '1') {
		sceneManager.reloadScene();
	}
}

void GameplayScene::draw() {
	colliders = manager.getGroupMembers(COLLIDERS);
	players = manager.getGroupMembers(PACMAN);
	tiles = manager.getGroupMembers(MAP);
	pellets = manager.getGroupMembers(PELLETS);

	for (auto it = tiles.begin(); it != tiles.end(); it++) {
		(*it)->draw();
	}
	for (auto it = pellets.begin(); it != pellets.end(); it++) {
		(*it)->draw();
	}
	for (auto it = ghosts.begin(); it != ghosts.end(); it++) {
		(*it)->draw();
	}
	for (auto it = players.begin(); it != players.end(); it++) {
		(*it)->draw();
	}

	// points.draw();
	// fps.draw();
	// pauseButton.draw();
	// reloadButton.draw();
}

void GameplayScene::pacmanInit() {
	pacmanPos = &pacman.addComponent<Transform>(
		PACMAN_SPAWN.x * (MAP_TILE_SIZE * MAP_TILE_SCALE) + MAP_PADDING.x + 1,
		PACMAN_SPAWN.y * (MAP_TILE_SIZE * MAP_TILE_SCALE) + MAP_PADDING.y + 1,
		50,
		50,
		(MAP_TILE_SCALE - 0.03f)
	);
	pacmanColl = &pacman.addComponent<Collider>(
		"pacman",
		[this](Collider& other) {
			if (other.tag == PELLET_TAG) {
				*pointVal += VALUE_PER_PELLET;
				other.entity->disable();
			}
		},
		false,
		false,
		false,
		false
	);
	pacman.addComponent<Sprites>("./sprites/pacman_move.png");
	Animator& pacmanAnim = pacman.addComponent<Animator>();
	pacmanAnim.addAnimation("idle", "./sprites/pacman_move.png");
	pacmanAnim.addEdge(ANIM_ENTRY, "idle", { std::shared_ptr<bool>(new bool(true)) });
	controller = &pacman.addComponent<Controller>();
	if (!pacman.hasGroup(PACMAN)) {
		pacman.addGroup(PACMAN);
	}
	addEntityToScene(pacman);
}

void GameplayScene::mapInit() {
	map = std::make_shared<Map>();
	map->init();
	map->drawMap();
	map->loadMap();
}
