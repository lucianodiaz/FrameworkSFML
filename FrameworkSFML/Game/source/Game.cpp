#include <Game.h>
#include <ECS/System/SystemRender.h>
#include <ECS/System/CollisionSystem.h>
#include <ECS/System/RotationSystem.h>
#include <ECS/System/TransformSystem.h>

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


	const int numBarrels = 19;
	const float circleRadius = 200.0f;  // Radio del círculo
	const float angleIncrement = (2 * 3.14159) / numBarrels;  // Incremento angular

	for (int i = 0; i < numBarrels; i++)
	{
		float angle = i * angleIncrement;  // Ángulo para la posición en el círculo
		float xPos = x + circleRadius * std::cos(angle);  // Calcular la posición x
		float yPos = y + circleRadius * std::sin(angle);  // Calcular la posición y

		auto barrel = world->getEntityManager()->spawnEntity<Pawn>("barrel", Configuration::Textures::Barrel, sf::Vector2f(xPos, yPos));
		barrel->ComponentDrawable->layer = 0;
	}


	_player = world->getEntityManager()->spawnEntity<Player>("ship", Configuration::Textures::Ship, sf::Vector2f(x, y));

}
