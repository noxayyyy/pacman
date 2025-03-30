#include "Counters.h"

FPS::FPS(std::string inStr) : Text(inStr, 10, 0) {
	value = 0;
	frameIndex = 0;
	setTex((data + ": " + std::to_string(value)).c_str());
}

FPS::~FPS() {}

float FPS::calcAvg() {
	float avg = 0;
	for (auto x : frameCounts) {
		avg += x;
	}
	avg /= SAMPLE_COUNT;
	return avg;
}

void FPS::update() {
	frameCounts[frameIndex % SAMPLE_COUNT] = Game::deltaTime > 0 ? 1.0f / Game::deltaTime : 0.0f;
	if (frameIndex++ % SAMPLE_COUNT) return;

	value = calcAvg();
	SDL_DestroyTexture(textTex);
	setTex((data + ": " + std::to_string(value)).c_str());
}

void FPS::reload() {
	value = 0;
	frameIndex = 0;
}

Points::Points(std::string inStr) : Text(inStr, 1100, 0) {
	value = 0;
	prevValue = -1;
	setTex((data + ": " + std::to_string(value)).c_str());
}

Points::~Points() {}

void Points::update() {
	if (value == prevValue) return;

	prevValue = value;
	SDL_DestroyTexture(textTex);
	setTex((data + ": " + std::to_string(value)).c_str());
}

void Points::reload() {
	value = 0;
	prevValue = -1;
}
