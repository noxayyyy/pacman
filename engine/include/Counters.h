#pragma once

#include "Text.h"
#include <SDL2/SDL_render.h>

struct FPS : public Text {
public:
	using Text::Text;

	int value;

	FPS(std::string inStr);
	~FPS();

	float calcAvg();
	void update() override;
	void reload() override;

private:
	float frameCounts[SAMPLE_COUNT];
	int frameIndex;
};

struct Points : public Text {
public:
	using Text::Text;

	int value;

	Points(std::string inStr);
	~Points();

	void update() override;
	void reload() override;

private:
	int prevValue;
};
