#pragma once
#include <iostream>
#include <algorithm>
#include <functional>  
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <SFML/System/Time.hpp>

using std::vector;
using std::string;
using std::shared_ptr;
using std::map;
using std::list;

template<typename T>
class EntityManager
{
	list<shared_ptr<T>> _entitiesToAdd;
	list<shared_ptr<T>> _entities;
	map<string, list<shared_ptr<T>>> _entityMap;
	size_t _totalEntities = 0;
public:
	EntityManager(){};

	void update(sf::Time deltaTime);

	template<typename E, typename... Args>
	shared_ptr<E> spawnEntity(const string& tag,Args&& ... args);

	list<shared_ptr<T>>& getEntities();

	list<shared_ptr<T>>& getEntities(const string& tag);

	template<typename ...COMPONENT>
	list<shared_ptr<T>> getEntitiesWithComponent();

	
};


template<typename T>
inline void EntityManager<T>::update(sf::Time deltaTime)
{
	if (_entitiesToAdd.size() > 0)
	{
		_entities.splice(_entities.end(), _entitiesToAdd);
	}

	_entitiesToAdd.clear();

	_entities.remove_if([](const std::shared_ptr<T>& entity) {
		return !entity->isAlive();
		});

	for (auto e : _entities)
	{
		if (e->isAlive())
		{
			e->update(deltaTime);
		}
	}
}


template<typename T>
inline list<shared_ptr<T>>& EntityManager<T>::getEntities()
{
	return _entities;
}


template<typename T>
inline list<shared_ptr<T>>& EntityManager<T>::getEntities(const string& tag)
{
	return _entityMap[tag];
}

template<typename T>
template<typename E, typename ...Args>
inline shared_ptr<E> EntityManager<T>::spawnEntity(const string& tag, Args&& ...args)
{
	auto e = std::shared_ptr<E>(new E(tag, _totalEntities++, std::forward<Args>(args)...));
	_entitiesToAdd.push_back(e);
	return e;
}

template<typename T>
template<typename ...COMPONENT>
inline list<shared_ptr<T>> EntityManager<T>::getEntitiesWithComponent()
{
	list<shared_ptr<T>> entitiesWithComponent;

	for (const auto& entity : _entities)
	{
		if (entity->isAlive())
		{
			if ((entity->template hasComponent<COMPONENT>() && ...))
			{
				entitiesWithComponent.push_back(entity);
			}
		}

	}

	return entitiesWithComponent;
}
