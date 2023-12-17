#pragma once

#include <iostream>
#include <vector>
#include <Builder.h>

class BuilderSpawner {
public:
	BuilderSpawner();
	~BuilderSpawner();

	void init();
	std::vector<bool> updateActivity(std::vector<std::vector<std::string>> imgArr);
	void moveBuilders();

	int x, y;

	Builder* firstBuilder;
	Builder* secondBuilder;
	Builder* thirdBuilder;
	std::vector<Builder*> builders;
	const std::string pathStr = "255 255 255";
};
	