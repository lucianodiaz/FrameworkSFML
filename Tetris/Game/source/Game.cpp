#include <Game.h>
#include <ECS/System/SystemRender.h>
#include <ECS/System/CollisionSystem.h>

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

	world->addSystem<SystemRender>();

	sf::FloatRect worldBounds(0.0f, 0.0f, 800, 600);
	int maxEntities=15;
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


	auto barrel = world->getEntityManager()->spawnEntity<Pawn>("barrel", Configuration::Textures::Barrel, sf::Vector2f(x + 200, y));
	barrel->ComponentDrawable->layer = 1;
	auto barrel1 = world->getEntityManager()->spawnEntity<Pawn>("barrel", Configuration::Textures::Barrel, sf::Vector2f(x - 200, y));
	barrel1->ComponentDrawable->layer = 1;
	auto barrel4 = world->getEntityManager()->spawnEntity<Pawn>("barrel", Configuration::Textures::Barrel, sf::Vector2f(x, y- 200));
	barrel4->ComponentDrawable->layer = 1;
	auto barrel5 = world->getEntityManager()->spawnEntity<Pawn>("barrel", Configuration::Textures::Barrel, sf::Vector2f(x, y+ 200));
	auto barrel6 = world->getEntityManager()->spawnEntity<Pawn>("barrel", Configuration::Textures::Barrel, sf::Vector2f(x+ 200, y + 200));
	//barrel->CollisionComponent->isBlocking = true;

	_player = world->getEntityManager()->spawnEntity<Player>("player", Configuration::Textures::Human, sf::Vector2f(x, y));

}
