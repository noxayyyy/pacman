#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using GroupID = std::size_t;

inline ComponentID getNewComponentTypeID() {
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

using GroupBitSet = std::bitset<maxGroups>;

class Component {
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	
	virtual ~Component() {}
};

class Entity {
public:
	Entity(Manager& memManager) : manager(memManager) {}

	void update() {
		for (auto& x : components) x->update();
	}
	
	void draw() {
		for (auto& x : components) x->draw();
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }
	bool hasGroup(GroupID memGroup) { return groupBitSet[memGroup]; }
	void addGroup(GroupID memGroup);
	void delGroup(GroupID memGroup) { groupBitSet[memGroup] = false; }

	template <typename T> bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
		T* x(new T(std::forward<TArgs>(mArgs)...));
		x->entity = this;
		std::unique_ptr<Component> uPtr{ x };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = x;
		componentBitSet[getComponentTypeID<T>()] = true;
		
		x->init();
		return *x;
	}

	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
	// use it like: gameObject.getComponent<PositionComponent>().setXpos(25);

private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
};

class Manager {
public:
	void update() {
		for (auto& x : entities) x->update();
	}

	/*void draw() {
		for (auto& x : entities) x->draw();
	}*/

	void refresh() {
		for (auto i(0u); i < maxGroups; i++) {
			auto& vec(groupedEntities[i]);
			vec.erase(std::remove_if(vec.begin(), vec.end(),
				[i](Entity* memEntity) {
					return !memEntity->isActive() || !memEntity->hasGroup(i);
				}), vec.end());
		}

		entities.erase(std::remove_if(entities.begin(), entities.end(),
			[](const std::unique_ptr<Entity>& mEntity) {
				return !mEntity->isActive();
			}), entities.end());
	}

	void addToGroup(Entity* memEntity, GroupID memGroup) { groupedEntities[memGroup].emplace_back(memEntity); }

	std::vector<Entity*>& getGroupMembers(GroupID memGroup) { return groupedEntities[memGroup]; }

	Entity& addEntity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};
