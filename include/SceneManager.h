#pragma once

#include <vector>
#include <algorithm>
#include <Scene.h>

extern Manager manager;

class SceneManager {
public:
	void loadScene(std::string id) {
		Scene* toBeLoaded = getSceneById(id);
		if (!toBeLoaded) return;

		if (currentScene && toBeLoaded->getIsPanel()) {
			bgScenes[currentScene->layer] = currentScene;
		} else if (currentScene) {
			currentScene->disableScene();
			manager.refresh(); // check if this works with multiple scenes
		}
		currentScene = toBeLoaded;
		toBeLoaded = nullptr;
		currentSceneIndex = currentScene->buildIndex;

		currentScene->init();
	}

	void loadScene(int buildIndex) {
		if (buildIndex > MAX_SCENE_COUNT) return;

		Scene* toBeLoaded = scenes[buildIndex];
		if (!toBeLoaded) return;


		if (currentScene && toBeLoaded->getIsPanel()) {
			bgScenes[currentScene->layer] = currentScene;
		} else if (currentScene) {
			currentScene->disableScene();
			manager.refresh(); // check if this works with multiple scenes
		}
		currentScene = toBeLoaded;
		toBeLoaded = nullptr;
		currentSceneIndex = currentScene->buildIndex;

		currentScene->init();
	}

	void loadNextScene() {
		loadScene(currentSceneIndex == MAX_SCENE_COUNT - 1 ? 0 : currentSceneIndex + 1);
	}

	void loadPrevScene() {
		loadScene(!currentSceneIndex ? MAX_SCENE_COUNT - 1 : currentSceneIndex - 1);
	}

	Scene* getCurrentScene() {
		return currentScene;
	}

	void addScene(Scene* scene) {
		if (
			scene->buildIndex > MAX_SCENE_COUNT ||
			scenes[scene->buildIndex] != nullptr ||
			getSceneById(scene->name) != nullptr
		) return;
		
		scenes[scene->buildIndex] = scene;
	}

	void removeBgScene(int layer) {
		if (layer > MAX_SCENE_COUNT || !bgScenes[layer]) return;
		bgScenes[layer] = NULL;
	}

	void updateScene() {
		for (auto& x : bgScenes) {
			if (!x) continue;
			x->update();
		}
		currentScene->update();
	}

	void callSceneEvents(SDL_Event& event) {
		currentScene->handleEvents(event);
		if (currentScene->getIsLocking()) return;
		for (auto& x : bgScenes) {
			if (!x) continue;
			x->handleEvents(event);
		}
	}

	void drawScene() {
		for (int i = 0; i < MAX_SCENE_COUNT; i++) {
			if (!scenes[i]) continue;
			if (scenes[i] != bgScenes[i] && scenes[i] != currentScene) continue;
			scenes[i]->draw();
		}
	}

	void reloadScene() {
		currentScene->reload();
	}

private:
	static const int MAX_SCENE_COUNT = 10;
	Scene* scenes[MAX_SCENE_COUNT];
	Scene* bgScenes[MAX_SCENE_COUNT];
	Scene* currentScene;
	int currentSceneIndex;

	Scene* getSceneById(std::string id) {
		auto it = std::find_if(
			std::begin(scenes),
			std::end(scenes),
			[id](Scene* x) { return x ? x->name == id : false; }
		);
		return it != std::end(scenes) ? *it : nullptr;
	}
};
