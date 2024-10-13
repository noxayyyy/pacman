#include <ECS.h>
#include <Game.h>

void Entity::addGroup(GroupID memGroup) {
	groupBitSet[memGroup] = true;
	manager.addToGroup(this, memGroup);
}

void Manager::destroyAll() {
	for (auto& x : entities) {
		x->deleteAllComponents();
		x->disable();
	}
	refresh();
}

void Entity::deleteAllComponents() {
	for (auto& x : this->components) {
		this->delComponent<decltype(x)>();
	}
}
