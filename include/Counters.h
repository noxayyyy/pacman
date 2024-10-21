#pragma once

#include <SDL2/SDL_render.h>
#include <Text.h>

class FPS : public Text {
public:
	using Text::Text;

	int value;
	FPS(std::string inStr) : Text(inStr, 10, 0) {
		value = 0;
		frameIndex = 0;
		setTex((data + ": " + std::to_string(value)).c_str());
	}

	float calcAvg() {
		float avg = 0;
		for (auto x : frameCounts) {
			avg += x;
		}
		avg /= SAMPLE_COUNT;
		return avg;
	}

	void update() override {
		frameCounts[frameIndex % SAMPLE_COUNT] = Game::deltaTime > 0 ? 1.0f / Game::deltaTime : 0.0f;
		if (frameIndex++ % SAMPLE_COUNT) return;

		value = calcAvg();
		SDL_DestroyTexture(textTex);
		setTex((data + ": " + std::to_string(value)).c_str());
	}

	void reload() override {
		value = 0;
		frameIndex = 0;
	}

private:
	static const int SAMPLE_COUNT = 10;
	float frameCounts[SAMPLE_COUNT];
	int frameIndex;
};

class Points : public Text {
public:
	using Text::Text;

	int value;

	Points(std::string inStr) : Text(inStr, 1100, 0) {
		value = 0;
		prevValue = -1;
		setTex((data + ": " + std::to_string(value)).c_str());
	}

	void update() override {
		if (value == prevValue) return;

		prevValue = value;
		SDL_DestroyTexture(textTex);
		setTex((data + ": " + std::to_string(value)).c_str());
	}

	void reload() override {
		value = 0;
		prevValue = -1;
	}

private:
	int prevValue;
};
