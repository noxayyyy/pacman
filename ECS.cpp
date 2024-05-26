#include <ECS.h>
#include <Game.h>

void Entity::addGroup(GroupID memGroup) {
	groupBitSet[memGroup] = true;
	manager.addToGroup(this, memGroup);
}

void Manager::destroyAll() {
	for (auto& x : entities) {
		if (x->hasGroup(Game::PACMAN)) {
			continue;
		}
		x->destroy();
	}
}

void Entity::deleteAllComponents() {
	for (auto& x : this->components) {
		this->delComponent<decltype(x)>();
	}
}