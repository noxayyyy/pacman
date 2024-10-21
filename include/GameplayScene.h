#include <Game.h>
#include <Scene.h>
#include <Counters.h>
#include <Map.h>
#include <Controller.h>
#include <Button.h>
#include <SceneManager.h>

extern Manager manager;
extern SceneManager sceneManager;
extern Controller* controller;

extern std::vector<Entity*>& colliders;
extern std::vector<Entity*>& tiles;
extern std::vector<Entity*>& players;
extern std::vector<Entity*>& ghosts;
extern std::vector<Entity*>& pellets;
extern std::vector<Entity*>& ghostSpawns;

static const int VALUE_PER_PELLET = 10;

class GameplayScene : public Scene {
public:
	GameplayScene() :
		Scene("Gameplay", 0, false, true, 0),
		pacman(manager.addEntity("pacman")),
		fps(manager.addEntity("fps")),
		points(manager.addEntity("points")),
		pauseButton(manager.addEntity("pauseButton"))
	{ }

	~GameplayScene() override {
		pacman.deleteAllComponents();
		fps.deleteAllComponents();
		points.deleteAllComponents();
		pauseButton.deleteAllComponents();

		free(pacmanPos);
		free(pacmanColl);
		pacmanPos = nullptr;
		pacmanColl = nullptr;

		manager.destroyAll();
		manager.refresh();

		map.reset();
	}

	void init() override {
		pacmanInit();
		mapInit();

		pelletCount = map->getPelletCount();

		fps.addComponent<FPS>("FPS");
		pointVal = &points.addComponent<Points>("POINTS").value;
		pauseButton.addComponent<Button>(
			"PAUSE",
			1366 - 132,
			768 - 68,
			128,
			64,
			[]() {
				Game::setPause(!Game::getPaused());
				sceneManager.loadNextScene();
			}
		);

		addEntityToScene(fps);
		addEntityToScene(points);
		addEntityToScene(pauseButton);
		
		colliders = manager.getGroupMembers(Game::COLLIDERS);
		players = manager.getGroupMembers(Game::PACMAN);
		tiles = manager.getGroupMembers(Game::MAP);
		pellets = manager.getGroupMembers(Game::PELLETS);

		enableScene();
	}

	void update() override {
		Vector2D lastVel = controller->updateVel();
		collisionResponse(lastVel);
		checkCollisions();

		points.update();
		fps.update();
		pauseButton.update();
		
		if (pelletCount == *pointVal / VALUE_PER_PELLET) {
			reload();
			pelletCount += map->getPelletCount();
		}
	}

	void reload() override {
		pacman.reload();

		for (auto& t : tiles) {
			t->disable();
			removeEntityFromScene(t);
		}
		manager.refresh();
		map->reloadMap();

		colliders = manager.getGroupMembers(Game::COLLIDERS);
		tiles = manager.getGroupMembers(Game::MAP);
		pellets = manager.getGroupMembers(Game::PELLETS);

		enableScene();
	}

	void handleEvents(SDL_Event& event) override {
		switch (event.type) {
		case SDL_KEYDOWN:
			controller->updateKeyDown(event.key.keysym.sym);
			break;	
		case SDL_KEYUP:
			controller->updateKeyUp(event.key.keysym.sym);
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&Game::mouseRect.x, &Game::mouseRect.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			Game::mouseButtonPressed = true;
			break;
		case SDL_MOUSEBUTTONUP:
			Game::mouseButtonPressed = false;
			break;
		default:
			break;
		}
	}

	void draw() override {
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

		points.draw();
		fps.draw();
		pauseButton.draw();
	}

private:
	Entity& pacman;
	Entity& fps;
	Entity& points;
	Entity& pauseButton;

	int* pointVal;
	int pelletCount;

	Transform* pacmanPos;
	Collider* pacmanColl;

	std::unique_ptr<Map> map;

	void pacmanInit() {
		pacmanPos = &pacman.addComponent<Transform>(
			Game::PACMAN_SPAWN[0] * 32 + Map::PADDING_X + 1,
			Game::PACMAN_SPAWN[1] * 32 + Map::PADDING_Y + 1
		);
		pacmanColl = &pacman.addComponent<Collider>("pacman");
		pacman.addComponent<Sprites>("./sprites/pacman-ghosts-red_00.png");
		controller = new Controller(&pacman);
		if (!pacman.hasGroup(Game::PACMAN)) {
			pacman.addGroup(Game::PACMAN);
		}
		addEntityToScene(pacman);
	}

	void mapInit() {
		map = std::make_unique<Map>();
		map->init();
		map->drawMap();
		map->loadMap();
	}

	void collisionResponse(Vector2D oldVel) {
		for (auto& memColl : colliders) {
			if (memColl->getComponent<Collider>().tag != "wall") continue;
			Collider coll = memColl->getComponent<Collider>();
			if (!Collision::AABBvel(*pacmanColl, coll)) continue;

			pacmanPos->vel.x = oldVel.x;
			pacmanPos->vel.y = oldVel.y;
			break;
		}
	}

	void collisionResponse() {
		for (auto& memColl : colliders) {
			if (memColl->getComponent<Collider>().tag != "wall") continue;
			if (!Collision::AABBvel(*pacmanColl, memColl->getComponent<Collider>())) continue;

			pacmanPos->vel.x = pacmanPos->vel.y = 0.0f;
			break;
		}
	}

	void checkCollisions() {
		collisionResponse();
		for (auto& p : pellets) {
			if (!p->isActive() || !Collision::AABB(*pacmanColl, p->getComponent<Collider>())) continue;
			*pointVal += VALUE_PER_PELLET;
			p->disable();
		}
	}
};
