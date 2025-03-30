#pragma once

#include "Constants.h"
#include <algorithm>
#include <array>
#include <bitset>
#include <memory>
#include <string>
#include <vector>

struct Component;
struct Entity;
struct Manager;

using ComponentID = std::size_t;
using GroupID = std::size_t;

inline ComponentID getNewComponentTypeID() {
	static ComponentID lastID = 0u;
	return lastID++;
}

template<typename T>
inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<std::shared_ptr<Component>, MAX_COMPONENTS>;

using GroupBitSet = std::bitset<MAX_GROUPS>;

struct Component {
public:
	Entity* entity;

	virtual void init() {}

	virtual void update() {}

	virtual void reload() {}

	virtual void draw() {}

	virtual ~Component() {}
};

struct Entity {
public:
	Entity(Manager& memManager, std::string _id);

	void update();
	void draw();

	bool isActive() const;
	std::string getID() const;

	void enable();
	void disable();
	void refresh();
	void reload();

	bool hasGroup(GroupID memGroup);
	void delGroup(GroupID memGroup);
	void addGroup(GroupID memGroup);

	template<typename T>
	bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template<typename T>
	void delComponent() {
		componentBitSet[getComponentTypeID<T>()] = false;
		components.erase(
			std::remove_if(
				components.begin(),
				components.end(),
				[this](const std::shared_ptr<Component>& mComponent) { return hasComponent<T>(); }
			),
			components.end()
		);
	}

	void deleteAllComponents();

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		if (hasComponent<T>()) {
			return *std::static_pointer_cast<T>(componentArray[getComponentTypeID<T>()]);
		}

		std::shared_ptr<T> x(new T(std::forward<TArgs>(mArgs)...));
		x->entity = this;
		components.emplace_back(x);

		componentArray[getComponentTypeID<T>()] = x;
		componentBitSet[getComponentTypeID<T>()] = true;

		x->init();
		return *x;
	}

	template<typename T>
	T& getComponent() const {
		return *std::static_pointer_cast<T>(componentArray[getComponentTypeID<T>()]);
	}

	// use it like: gameObject.getComponent<PositionComponent>().setXpos(25);

private:
	Manager& manager;
	bool active = false;
	std::string id;
	std::vector<std::shared_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
};

struct Manager {
public:
	Manager();

	void update();
	void draw();
	void refreshGroups();
	void refresh();

	void addToGroup(Entity* memEntity, GroupID memGroup);
	std::vector<Entity*>& getGroupMembers(GroupID memGroup);
	Entity& addEntity(std::string id);
	void destroyAll();

private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, MAX_GROUPS> groupedEntities;
};
