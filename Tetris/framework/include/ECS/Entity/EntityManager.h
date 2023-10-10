#pragma once

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

template<typename T>
class EntityManager
{
	vector<shared_ptr<T>> _toAdd;
	vector<shared_ptr<T>> _entities;
	map<string, vector<shared_ptr<T>>> _entityMap;
	size_t _totalEntities = 0;
public:
	EntityManager(){};

	void update(sf::Time deltaTime);

	template<typename E>

	shared_ptr<E> addEntity(const string& tag);

	vector<shared_ptr<T>>& getEntities();

	vector<shared_ptr<T>>& getEntities(const string& tag);

	template<typename ...COMPONENT>
	vector<shared_ptr<T>> getEntitiesWithComponent();

	
};


template<typename T>
inline void EntityManager<T>::update(sf::Time deltaTime)
{
	for (auto e : _toAdd)
	{
		_entities.push_back(e);
		_entityMap[e->tag()].push_back(e);
	}

	_toAdd.clear();

	for (auto e : _entities)
	{
		if (e->isAlive())
		{
			e->update(deltaTime);
		}
	}
}


template<typename T>
inline vector<shared_ptr<T>>& EntityManager<T>::getEntities()
{
	return _entities;
}


template<typename T>
inline vector<shared_ptr<T>>& EntityManager<T>::getEntities(const string& tag)
{
	return _entityMap[tag];
}

template<typename T>
template<typename E>
inline shared_ptr<E> EntityManager<T>::addEntity(const string& tag)
{
	auto e = std::shared_ptr<E>(new E(tag, _totalEntities++));
	_toAdd.push_back(e);
	return e;
}

template<typename T>
template<typename ...COMPONENT>
inline vector<shared_ptr<T>> EntityManager<T>::getEntitiesWithComponent()
{
	vector<shared_ptr<T>> entitiesWithComponent;

	for (const auto& entity : _entities)
	{
		if ((entity->template hasComponent<COMPONENT>() && ...))
		{
			entitiesWithComponent.push_back(entity);
		}
	}

	return entitiesWithComponent;
}
