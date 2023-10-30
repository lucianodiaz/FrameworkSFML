#include <Game.h>
#include <ECS/System/CollisionSystem.h>
#include <ECS/System/RotationSystem.h>
#include <ECS/System/TransformSystem.h>
#include <ECS/System/SystemRender.h>

Game::Game(int x, int y)
{
	world = World::getWorld();
	world->CreateWindow(x, y, "SFML Framework");
}

void Game::run(int frame_per_seconds)
{
	sf::Clock clock;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Time TimerPerFrame = sf::seconds(1.f / frame_per_seconds);

	createPlayer();

	world->addSystem<TransformSystem>();
	world->addSystem<RotationSystem>();
	world->addSystem<SystemRender>();

	sf::FloatRect worldBounds(0,0,world->getWindow()->getRenderWindow().getSize().x, world->getWindow()->getRenderWindow().getSize().y);
	int maxEntities=10;
	world->addSystem<CollisionSystem>(worldBounds, maxEntities);

	while (world->getWindow()->isOpen())
	{
		processEvents();
		bool repaint = false;
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimerPerFrame)
		{
			timeSinceLastUpdate -= TimerPerFrame;
			repaint = true;
			update(TimerPerFrame);
		}
		if (repaint)draw();
	}
}

Game::~Game()
{
}

void Game::update(sf::Time deltaTime)
{	
	world->update(deltaTime);

	//Only for pouporse of this game we need to change position of
	//ships and object in the game, when they are bound of the window
	//we need to tp them to other side
	//like an uclidean torus world
	auto entities = world->getEntityManager()->getEntities();

	for (auto& entity : entities)
	{
		sf::Vector2f& pos = entity->ComponentTransform->position;
		float xWorld = world->getWindow()->getRenderWindow().getSize().x;
		float yWorld = world->getWindow()->getRenderWindow().getSize().y;
		if (pos.x < 0)
		{
			pos.x = xWorld;
			pos.y = yWorld - pos.y;
		}
		else if (pos.x > xWorld)
		{
			pos.x = 0;
			pos.y = yWorld - pos.y;
		}
		if (pos.y < 0)
		{
			pos.y = yWorld;
		}
		else if (pos.y > yWorld)
		{
			pos.y = 0; 
		}

	}
}

void Game::draw()
{
	world->draw();
}

void Game::processEvents()
{
	sf::Event evt;
	while (world->getWindow()->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
			world->getWindow()->close();
		else if (evt.type == sf::Event::KeyPressed)
		{
			if (evt.key.code == sf::Keyboard::Escape)
			{
				world->getWindow()->close();
			}
		}
	}
	_player->processEvent();
}

void Game::createPlayer()
{
	float x = world->getWindow()->getRenderWindow().getSize().x / 2.0f;
	float y = world->getWindow()->getRenderWindow().getSize().y / 2.0f;

	_player = world->getEntityManager()->spawnEntity<Player>("ship", Configuration::Textures::Ship, sf::Vector2f(x, y));

}
