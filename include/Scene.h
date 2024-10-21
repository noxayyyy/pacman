#pragma once

#include <vector>
#include <ECS.h>
#include <Collider.h>

class Scene {
public:
	std::string name;
	int buildIndex;
	int layer;
	SDL_Rect mouseRect;
	bool mouseButtonPressed;

	Scene(std::string name, int buildIndex, bool isPanel, bool isLocking, int layer) {
		this->name = name;
		this->buildIndex = buildIndex;
		this->isPanel = isPanel;
		this->isLocking = isLocking;
		this->layer = layer;
		entities = std::vector<Entity*>();
	}

	virtual ~Scene() { };

	virtual void init() = 0; // remember to add the scene to the scene manager
	virtual void update() = 0;
	virtual void reload() = 0;
	virtual void handleEvents(SDL_Event& event) = 0;
	virtual void draw() = 0;

	void addEntityToScene(Entity& entity) {
		entities.emplace_back(&entity);
	}

	void removeEntityFromScene(Entity* entity) {
		entities.erase(std::find(entities.begin(), entities.end(), entity));
	}

	void clearScene() {
		disableScene();
		entities.clear();
	}

	void enableScene() {
		for (auto& e : entities) {
			e->enable();
		}
	}

	void disableScene() {
		for (auto& e : entities) {
			e->disable();
		}
	}

	const bool& getIsPanel() const {
		return isPanel;
	}

	const bool& getIsLocking() const {
		return isLocking;
	}

private:
	std::vector<Entity*> entities;
	bool isPanel;
	bool isLocking;
};
