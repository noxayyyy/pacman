#include "Game.h"
#include <Scene.h>
#include <Counters.h>
#include <Map.h>
#include <Controller.h>

extern Manager manager;

extern Controller* controller;

extern std::vector<Entity*>& colliders;
extern std::vector<Entity*>& tiles;
extern std::vector<Entity*>& players;
extern std::vector<Entity*>& ghosts;
extern std::vector<Entity*>& pellets;
extern std::vector<Entity*>& ghostSpawns;

class GameplayScene : public Scene {
public:
	GameplayScene() : Scene("Gameplay", 0, false, true, 0), pacman(manager.addEntity("pacman")) { }

	~GameplayScene() override {
		pacman.deleteAllComponents();
		free(pacmanPos);
		free(pacmanColl);
		manager.destroyAll();
		manager.refresh();
		map.reset();
		fps.reset();
		points.reset();
	}

	void init() override {
		fps = std::make_unique<FPS>("FPS");
		points = std::make_unique<Points>("POINTS");

		pacmanInit();
		mapInit();
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
		points->update();
		fps->update();
		
		if (std::all_of(pellets.begin(), pellets.end(), [](Entity* e) {
			return !e->isActive();
		})) {
			reload();
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
		points->value = 0;
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
		points->draw();
		fps->draw();
	}

private:
	Entity& pacman;
	Transform* pacmanPos;
	Collider* pacmanColl;

	std::unique_ptr<Map> map;
	std::unique_ptr<FPS> fps;
	std::unique_ptr<Points> points;

	void pacmanInit() {
		pacman.addComponent<Transform>(
			Game::PACMAN_SPAWN[0] * 32 + Map::PADDING_X + 1,
			Game::PACMAN_SPAWN[1] * 32 + Map::PADDING_Y + 1
		);
		pacman.addComponent<Sprites>("./sprites/pacman-ghosts-red_00.png");
		pacman.addComponent<Collider>("pacman");
		controller = new Controller(&pacman);
		if (!pacman.hasGroup(Game::PACMAN)) {
			pacman.addGroup(Game::PACMAN);
		}
		pacmanPos = &pacman.getComponent<Transform>();
		pacmanColl = &pacman.getComponent<Collider>();

		addEntityToScene(pacman);
	}

	void mapInit() {
		if (map) {
			map->LoadMap();
			tiles = manager.getGroupMembers(Game::MAP);
			pellets = manager.getGroupMembers(Game::PELLETS);
			ghostSpawns = manager.getGroupMembers(Game::GHOST_BAR);
			return;
		}
		map = std::make_unique<Map>();
		map->init();
		map->DrawMap();
		map->LoadMap();
	}

	void collisionResponse(Vector2D oldVel) {
		for (auto& memColl : colliders) {
			if (memColl->getComponent<Collider>().tag != "wall") {
				continue;
			}
			Collider coll = memColl->getComponent<Collider>();
			if (Collision::AABBvel(*pacmanColl, coll)) {
				pacmanPos->vel.x = oldVel.x;
				pacmanPos->vel.y = oldVel.y;
				break;
			}
		}
	}

	void collisionResponse() {
		for (auto& memColl : colliders) {
			if (memColl->getComponent<Collider>().tag != "wall") {
				continue;
			}
			if (!Collision::AABBvel(*pacmanColl, memColl->getComponent<Collider>())) {
				continue;
			}
			pacmanPos->vel.x = pacmanPos->vel.y = 0.0f;
			break;
		}
	}

	void checkCollisions() {
		collisionResponse();
		for (auto& p : pellets) {
			if (!p->isActive() || !Collision::AABB(*pacmanColl, p->getComponent<Collider>())) {
				continue;
			}
			points->value += 10;
			p->disable();
		}
	}
};
