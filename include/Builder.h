#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

class Builder {
public:
	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};
	
	Builder();
	~Builder();

	void init();
	void updateChance();
	void updateForceChange();
	void assignDirection();
	void setActive(bool val) { active = val; }
	bool isActive() { return active; }

	int x, y;
	const int MAX_STEP = 3;
	int currCount;
	Direction currDir;
	Direction prevDir;
	bool forceChange;
	bool chanceChange;

private:
	bool active;
};