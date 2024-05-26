#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

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

	void init();
	void updateChance();
	void updateForceChange();
	void assignDirection();
	bool updateActivity(char currBlock, char prevBlock);

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
	~BuilderSpawner() = default;

	void init();
	void moveBuilders();
	void updateBuilders();

	bool isActive() {
		return firstBuilder->isActive() || 
			secondBuilder->isActive() || 
			thirdBuilder->isActive();
	}

	int x, y;

	std::shared_ptr<Builder> firstBuilder;
	std::shared_ptr<Builder> secondBuilder;
	std::shared_ptr<Builder> thirdBuilder;
	std::vector<std::shared_ptr<Builder>> builders;
private:
	const char path = 'p';
	static const int MAP_WIDTH = 20; // 20
	static const int MAP_HEIGHT = 24; // 22
};
	