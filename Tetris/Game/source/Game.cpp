#include <Game.h>
#include <ECS/System/SystemRender.h>
#include <ECS/System/CollisionSystem.h>

Game::Game(int x, int y) :
	_window(std::make_unique<Window>(x,y,"SFML Framework"))
{
	_entityManager = std::make_shared<EntityManager<Actor>>();
}

void Game::run(int frame_per_seconds)
{
	sf::Clock clock;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Time TimerPerFrame = sf::seconds(1.f / frame_per_seconds);

	createPlayer();

	std::unique_ptr<TransformSystem> _transformSystem = std::make_unique<TransformSystem>();
	_transformSystem->setEntityManager(_entityManager);
	_systems.push_back(std::move(_transformSystem));

	std::unique_ptr<SystemRender> _renderSystem = std::make_unique<SystemRender>(_window->getRenderWindow());
	_renderSystem->setEntityManager(_entityManager);
	_systems.push_back(std::move(_renderSystem));

	std::unique_ptr<CollisionSystem> _collisionSystem = std::make_unique<CollisionSystem>();
	_collisionSystem->setEntityManager(_entityManager);
	_systems.push_back(std::move(_collisionSystem));

	while (_window->isOpen())
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
	for (auto& s : _systems)
	{
		s->update(deltaTime);
	}
	_entityManager->update(deltaTime);
}

void Game::draw()
{
	/*_window->clear();
	_window->display();*/
}

void Game::processEvents()
{
	sf::Event evt;
	while (_window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
			_window->close();
		else if (evt.type == sf::Event::KeyPressed)
		{
			if (evt.key.code == sf::Keyboard::Escape)
			{
				_window->close();
			}
		}
	}
	_player->processEvent();
}

void Game::createPlayer()
{
	float x = _window->getRenderWindow().getSize().x / 2.0f;
	float y = _window->getRenderWindow().getSize().y / 2.0f;


	auto barrel = _entityManager->addEntity<Pawn>("barrel", Configuration::Textures::Barrel, sf::Vector2f(x + 64, y));
	barrel->CollisionComponent->isBlocking = true;

	_player = _entityManager->addEntity<Player>("player", Configuration::Textures::Human, sf::Vector2f(x, y));

}
