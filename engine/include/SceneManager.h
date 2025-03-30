#pragma once

#include "Scene.h"

extern Manager manager;

struct SceneManager {
public:
	SceneManager() {}

	~SceneManager() {}

	void loadScene(std::string id);
	void loadScene(int buildIndex);
	void loadNextScene();
	void loadPrevScene();

	Scene* getCurrentScene();
	void addScene(Scene* scene);
	void removeBgScene(int layer);

	void updateScene();
	void callSceneEvents(SDL_Event& event);
	void drawScene();
	void reloadScene();

private:
	Scene* scenes[MAX_SCENE_COUNT];
	Scene* bgScenes[MAX_SCENE_COUNT];
	Scene* currentScene;
	int currentSceneIndex;

	Scene* getSceneById(std::string id);
};
