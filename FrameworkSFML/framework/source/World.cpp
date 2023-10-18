#include "World.h"

World::World()
{
	_entityManager = std::make_shared<EntityManager<Actor>>();
}

void World::CreateWindow(int width, int height, string tittle)
{
	_window = std::make_unique<Window>(width, height, tittle);
}

void World::update(sf::Time deltaTime)
{
	_entityManager->update(deltaTime);
	for (auto& s : _systems)
	{
		s->update(deltaTime);
	}
	
}

void World::draw()
{
	_window->clear();
	for (auto& s : _systems)
	{
		s->draw(_window->getRenderWindow());
	}
	_window->display();
}
