#include <ECS.h>
#include <Game.h>

void Entity::addGroup(GroupID memGroup) {
	groupBitSet[memGroup] = true;
	manager.addToGroup(this, memGroup);
}

