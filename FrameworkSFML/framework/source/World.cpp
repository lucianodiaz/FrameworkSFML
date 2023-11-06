#include "World.h"
#include "Math/Random.h"

World::World()
{
	_entityManager = std::make_shared<EntityManager<Actor>>();
	randomlib::rand_init();
}

void World::CreateWindow(int width, int height, string tittle)
{
	_window = std::make_unique<Window>(width, height, tittle);

	addSystem<TransformSystem>();
	addSystem<RotationSystem>();
	addSystem<SystemRender>();
	addSystem<CameraSystem>();

	sf::FloatRect worldBounds(0, 0, getWindow()->getRenderWindow().getSize().x, getWindow()->getRenderWindow().getSize().y);
	int maxEntities = 15;
	addSystem<CollisionSystem>(worldBounds, maxEntities);
}

void World::update(sf::Time deltaTime)
{
	_entityManager->update(deltaTime);
	for (auto& s : _systems)
	{
		s->update(deltaTime);
	}
	timerManager.update();
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
