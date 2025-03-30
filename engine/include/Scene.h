#pragma once

#include "Collider.h"
#include "ECS.h"
#include <vector>

struct Scene {
public:
	std::string name;
	int buildIndex;
	int layer;
	bool mouseButtonPressed;

	Scene(std::string name, int buildIndex, bool isPanel, bool isLocking, int layer);

	virtual ~Scene() {}

	virtual void init() = 0; // remember to add the scene to the scene manager
	virtual void update() = 0;
	virtual void reload() = 0;
	virtual void reloadWithState() = 0;
	virtual void handleEvents(SDL_Event& event) = 0;
	virtual void draw() = 0;

	void addEntityToScene(Entity& entity);
	void removeEntityFromScene(Entity* entity);
	bool existsInScene(Entity* entity);
	void clearScene();
	void enableScene();
	void disableScene();

	const bool& getIsPanel() const;
	const bool& getIsLocking() const;

private:
	std::vector<Entity*> entities;
	bool isPanel;
	bool isLocking;
};
