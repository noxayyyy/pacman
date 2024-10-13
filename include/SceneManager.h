#include <vector>
#include <algorithm>
#include <Scene.h>

class SceneManager {
public:
	void loadScene(std::string id) {
		Scene* toBeLoaded = getSceneById(id);
		if (!toBeLoaded) {
			return;
		}
		if (currentScene && currentScene->getIsPanel()) {
			bgScenes[currentScene->layer] = currentScene;
		}
		currentScene = toBeLoaded;
		currentSceneIndex = currentScene->buildIndex;
		currentScene->init();
	}

	void loadScene(int buildIndex) {
		if (buildIndex > maxSceneCount) {
			return;
		}

		Scene* toBeLoaded = scenes[buildIndex];
		if (!toBeLoaded) {
			return;
		}

		if (currentScene && currentScene->getIsPanel()) {
			bgScenes[currentScene->layer] = currentScene;
		}
		currentScene = toBeLoaded;
		currentSceneIndex = currentScene->buildIndex;
		currentScene->init();
	}

	void loadNextScene() {
		loadScene(currentSceneIndex == maxSceneCount - 1 ? 0 : currentSceneIndex + 1);
	}

	void loadPrevScene() {
		loadScene(!currentSceneIndex ? maxSceneCount - 1 : currentSceneIndex - 1);
	}

	Scene* getCurrentScene() {
		return currentScene;
	}

	void addScene(Scene* scene) {
		if (
			scene->buildIndex > maxSceneCount ||
			scenes[scene->buildIndex] != nullptr ||
			getSceneById(scene->name) != nullptr
		) {
			return;
		}
		scenes[scene->buildIndex] = scene;
	}

private:
	static const int maxSceneCount = 10;
	Scene* scenes[maxSceneCount];
	Scene* bgScenes[maxSceneCount];
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
