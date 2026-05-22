#include "GameplayScene.h"

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
	: Scene("Gameplay", 0, false, true, 0), pacman(manager.addEntity(PACMAN_TAG)),
	  // fps(manager.addEntity("fps")), points(manager.addEntity("points")),
	  pauseButton(manager.addEntity("pauseButton")),
	  reloadButton(manager.addEntity("reloadButton")) {}

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
	pauseButton.addComponent<Button>("PAUSE", 1234, 700, 128, 64, []() {
		Game::setPause(!Game::getPaused());
		// sceneManager.loadNextScene();
	});
	reloadButton.addComponent<Button>("RELOAD", 8, 700, 128, 64, []() {
		sceneManager.reloadScene();
	});

	// addEntityToScene(fps);
	// addEntityToScene(points);
	addEntityToScene(pauseButton);
	addEntityToScene(reloadButton);

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

	for (auto& t : tiles) {
		t->disable();
		removeEntityFromScene(t);
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
	pauseButton.reload();
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
}

void GameplayScene::draw() {
	colliders = manager.getGroupMembers(COLLIDERS);
	players = manager.getGroupMembers(PACMAN);
	tiles = manager.getGroupMembers(MAP);
	pellets = manager.getGroupMembers(PELLETS);

	for (auto& t : tiles) {
		t->draw();
	}
	for (auto& p : pellets) {
		p->draw();
	}
	for (auto& g : ghosts) {
		g->draw();
	}
	for (auto& p : players) {
		p->draw();
	}

	// points.draw();
	// fps.draw();
	pauseButton.draw();
	reloadButton.draw();
}

void GameplayScene::pacmanInit() {
	pacmanPos = &pacman.addComponent<Transform>(
		PACMAN_SPAWN.x * 32 + MAP_PADDING.x + 1, PACMAN_SPAWN.y * 32 + MAP_PADDING.y + 1
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
	map = std::make_unique<Map>();
	map->init();
	map->drawMap();
	map->loadMap();
}
