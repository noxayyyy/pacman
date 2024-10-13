#pragma once

#include <vector>
#include <algorithm>

class Builder {
public:
	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};
	
	Builder() = default;
	~Builder() = default;

	void init() {
		x = 0;
		y = 0;
		currCount = 0;
		currDir = NONE;
		prevDir = NONE;
		forceChange = false;
		chanceChange = false;
		active = true;
	}

	void updateChance() {
		chanceChange = rand() % 5 == 0;
	}

	void updateForceChange() {
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

	void assignDirection() {
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

	bool updateActivity(char currBlock, char prevBlock) {
		if (currBlock == path || prevBlock == path) {
			setActive(false);
		}
		return currBlock != path && prevBlock == path;
	}

	void setActive(bool val) {
		active = val;
	}
	bool isActive() {
		return active;
	}

	int x, y;
	const int MAX_STEP = 3;
	int currCount;
	Direction currDir;
	Direction prevDir;
	char currBlock;
	char prevBlock;
	bool forceChange;
	bool chanceChange;

private:
	const char path = 'p';
	bool active;
};

class BuilderSpawner {
public:
	BuilderSpawner() = default;

	~BuilderSpawner() {
		clear();
	}

	void init() {
		x = 0;
		y = 0;
		builders.push_back(Builder());
		builders.push_back(Builder());
		builders.push_back(Builder());
		builders[0].init();
		builders[1].init();
		builders[2].init();
	}

	void moveBuilders() {
		for (auto& build : builders) {
			if (!build.isActive()) {
				continue;
			}

			switch (build.currDir) {
			case Builder::UP:
				build.y -= 2;
				break;
			case Builder::DOWN:
				build.y += 2;
				break;
			case Builder::LEFT:
				build.x -= 2;
				break;
			case Builder::RIGHT:
				build.x += 2;
				break;
			default:
				break;
			}
			build.currCount++;
		}
	}

	void updateBuilders() {
		for (auto& build : builders) {
			build.updateChance();
			build.updateForceChange();
			build.assignDirection();
		}
	}

	bool isActive() {
		bool active = false;
		for (int i = 0; i < builders.size(); i++) {
			active |= builders[i].isActive();
		}
		return active;
	}

	void clear() {
		builders.clear();
	}

	int x, y;
	std::vector<Builder> builders;
private:
	static const int MAP_WIDTH = 20; // 20
	static const int MAP_HEIGHT = 24; // 22
};
	
