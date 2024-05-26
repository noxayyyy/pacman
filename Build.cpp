#include <Build.h>

//
// Builder Definitions
//

void Builder::init() {
	x = 0;
	y = 0;
	currCount = 0;
	currDir = NONE;
	prevDir = NONE;
	forceChange = false;
	chanceChange = false;
	active = true;
}

void Builder::updateChance() {
	chanceChange = rand() % 5 == 0;
}

void Builder::updateForceChange() {
	if (chanceChange || currCount >= MAX_STEP) {
		forceChange = true;
		return;
	}

	switch (currDir) {
	case UP:
		if (y - 2 < 1) {
			forceChange = true;
		}
		break;
	case DOWN:
		if (y + 2 > 20) {
			forceChange = true;
		}
		break;
	case LEFT:
		if (x - 2 < 1) {
			forceChange = true;
		}
		break;
	case RIGHT:
		if (x + 2 > 18) {
			forceChange = true;
		}
		break;
	case NONE:
		break;
	}
}

void Builder::assignDirection() {
	if (!active || !forceChange) {
		return;
	}
	std::vector<Direction> invalidDir = { NONE, NONE, NONE, NONE };

	if (y >= 19 || currDir == UP) {
		invalidDir[3] = DOWN;
	}
	if (x >= 17 || currDir == LEFT) {
		invalidDir[1] = RIGHT;
	}
	if (y <= 2 || currDir == DOWN) {
		invalidDir[2] = UP;
	}
	if (x <= 2 || currDir == RIGHT) {
		invalidDir[0] = LEFT;
	}

	prevDir = currDir;
	currDir = (Direction)(rand() % 4);

	while (std::find(invalidDir.begin(), invalidDir.end(), currDir) != invalidDir.end()) {
		currDir = (Direction)(rand() % 4);
	}
	currCount = 0;
	forceChange = false;
}

bool Builder::updateActivity(char currBlock, char prevBlock) {
	if (currBlock == path || prevBlock == path) {
		setActive(false);
	}
	return currBlock != path && prevBlock == path;
}

//
// BuilderSpawner Definitions
//

void BuilderSpawner::init() {
	x = 0; 
	y = 0;
	firstBuilder = std::make_shared<Builder>();
	secondBuilder = std::make_shared<Builder>();
	thirdBuilder = std::make_shared<Builder>();
	firstBuilder->init();
	secondBuilder->init();
	thirdBuilder->init();
	builders.push_back(firstBuilder);
	builders.push_back(secondBuilder);
	builders.push_back(thirdBuilder);
}


void BuilderSpawner::moveBuilders() {
	for (auto& build : builders) {
		if (!build->isActive()) {
			continue;
		}

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

void BuilderSpawner::updateBuilders() {
	for (auto& build : builders) {
		build->updateChance();
		build->updateForceChange();
		build->assignDirection();
	}
}