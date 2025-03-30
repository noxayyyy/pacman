#include "Sprites.h"
#include <memory>
#include <unordered_map>

struct Animator : public Component {
public:
	struct Animation {
		const char* id;
		int frames;
		SDL_Texture* texture;
		int speed = 100;
		bool loop;
		bool reversible = false;

		Animation();
		Animation(const char* id);
		Animation(
			const char* id, SDL_Point frameSize, const char* texPath, int speed = 100,
			bool isLooping = true, bool isReversible = false
		);
		~Animation();
	};

	struct Edge {
		std::vector<std::shared_ptr<bool>> conditions;

		Edge();
		Edge(std::vector<std::shared_ptr<bool>> conditions);
		~Edge();

		const bool canTraverse() const;
	};

	Animator();
	~Animator();

	void init() override;
	void update() override;
	void draw() override;

	void addAnimation(
		const char* id, const char* texPath, int speed = 100, const bool isLooping = true,
		const bool isReversible = false
	);
	void
	addEdge(const char* idFrom, const char* idTo, std::vector<std::shared_ptr<bool>> conditions);
	std::string getCurrAnimID();

private:
	std::shared_ptr<Animation> currentAnimation;

	Sprites* sprite;
	SDL_Point frameSize;

	std::unordered_map<const char*, Animation> animations;
	std::unordered_map<const char*, std::unordered_map<const char*, Edge>> adjMatrix;
};
