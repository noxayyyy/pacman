#include <BuilderSpawner.h> 

BuilderSpawner::BuilderSpawner() {}
BuilderSpawner::~BuilderSpawner() {}

void BuilderSpawner::init() {
	x = 0; y = 0;
	firstBuilder = new Builder();
	secondBuilder = new Builder();
	thirdBuilder = new Builder();
	firstBuilder->init();
	secondBuilder->init();
	thirdBuilder->init();
	builders.push_back(firstBuilder);
	builders.push_back(secondBuilder);
	builders.push_back(thirdBuilder);
}

std::vector<bool> BuilderSpawner::updateActivity(std::vector<std::vector<std::string>> imgArr) {
	std::vector<bool> killPrevBlock = { false, false, false };
	for (int i = 0; i < 3; i++) {
		if (imgArr[builders[i]->y][builders[i]->x] == pathStr) {
			builders[i]->setActive(false);
			continue;
		}

		switch (builders[i]->currDir) {
		case Builder::UP:
			if (imgArr[builders[i]->y + 1][builders[i]->x] != pathStr) break;
			builders[i]->setActive(false);
			killPrevBlock[i] = true;
			break;
		case Builder::DOWN:
			if (imgArr[builders[i]->y - 1][builders[i]->x] != pathStr) break;
			builders[i]->setActive(false);
			killPrevBlock[i] = true;
			break;
		case Builder::LEFT:
			if (imgArr[builders[i]->y][builders[i]->x + 1] != pathStr) break;
			builders[i]->setActive(false);
			killPrevBlock[i] = true;
			break;
		case Builder::RIGHT:
			if (imgArr[builders[i]->y][builders[i]->x - 1] != pathStr) break;
			builders[i]->setActive(false);
			killPrevBlock[i] = true;
			break;
		default:
			break;
		}
	}
	return killPrevBlock;
}

void BuilderSpawner::moveBuilders() {
	for (auto& build : builders) {
		if (!build->isActive()) continue;

		switch (build->currDir) {
		case Builder::UP:
			build->y -= 2;
			break;
		case Builder::DOWN:
			build->y += 2;
			break;
		case Builder::LEFT:
			build->x -= 2;
			break;
		case Builder::RIGHT:
			build->x += 2;
			break;
		default:
			break;
		}
		build->currCount++;
	}
}