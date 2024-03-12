#include <Builder.h> 

Builder::Builder() {}
Builder::~Builder() {}

void Builder::init() {
	x = 0; y = 0;
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