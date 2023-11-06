#include <Game.h>
#include <ECS/System/CollisionSystem.h>
#include <ECS/System/RotationSystem.h>
#include <ECS/System/TransformSystem.h>
#include <ECS/System/SystemRender.h>
#include <Enemy/Meteors/Meteor.h>
#include <Math/Random.h>
#include <ECS/System/CameraSystem.h>

Game::Game(int x, int y)
{
	world = World::getWorld();
	world->CreateWindow(x, y, "SFML Framework");
	cantAsteroids = 1;
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
	world->addSystem<CameraSystem>();

	sf::FloatRect worldBounds(0,0,world->getWindow()->getRenderWindow().getSize().x, world->getWindow()->getRenderWindow().getSize().y);
	int maxEntities=15;
	world->addSystem<CollisionSystem>(worldBounds, maxEntities);

	world->GetTimerManager().createTimer(10, 
		[this]() {
		createAsteroid();
		},true);

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

void Game::createAsteroid()
{
	std::cout << "Asteroids to create: " << cantAsteroids << std::endl;
	for (int i = 0; i < cantAsteroids; i++)
	{
		auto xw = randomlib::random(0, world->getWindow()->getWindowCenterPos().x);
		auto yw = randomlib::random(0, world->getWindow()->getWindowCenterPos().y);
		auto m = world->getEntityManager()->spawnEntity<Meteor>("meteor", Configuration::Textures::Barrel, sf::Vector2f(xw, yw));
	}
	cantAsteroids++;
}
