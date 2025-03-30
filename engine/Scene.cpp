#include "Scene.h"

Scene::Scene(std::string name, int buildIndex, bool isPanel, bool isLocking, int layer) {
	this->name = name;
	this->buildIndex = buildIndex;
	this->isPanel = isPanel;
	this->isLocking = isLocking;
	this->layer = layer;
	entities = std::vector<Entity*>();
}

void Scene::addEntityToScene(Entity& entity) {
	entities.emplace_back(&entity);
}

void Scene::removeEntityFromScene(Entity* entity) {
	if (!existsInScene(entity)) return;
	entities.erase(std::find_if(entities.begin(), entities.end(), [entity](Entity* e) {
		return e == entity;
	}));
}

bool Scene::existsInScene(Entity* entity) {
	if (std::find_if(entities.begin(), entities.end(), [entity](Entity* e) {
			return e == entity;
		}) == entities.end()) {
		return false;
	}
	return true;
}

void Scene::clearScene() {
	disableScene();
	entities.clear();
}

void Scene::enableScene() {
	for (auto& e : entities) {
		e->enable();
	}
}

void Scene::disableScene() {
	for (auto& e : entities) {
		e->disable();
	}
}

const bool& Scene::getIsPanel() const {
	return isPanel;
}

const bool& Scene::getIsLocking() const {
	return isLocking;
}
