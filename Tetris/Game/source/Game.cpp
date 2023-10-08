#include <Game.h>

Game::Game(int x, int y) :
	_window(std::make_unique<Window>(x,y,"Tetris"))
{
	_entityManager = std::make_shared<EntityManager<Actor>>();
}

void Game::run(int frame_per_seconds)
{
	sf::Clock clock;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Time TimerPerFrame = sf::seconds(1.f / frame_per_seconds);

	createPlayer();

	while (_window->isOpen())
	{
		//_entityManager->update(TimerPerFrame);

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
	_entityManager->update(deltaTime);
}

void Game::draw()
{
	_window->clear();

	_window->draw(_player->cDrawable->sprite);
	_window->display();
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
}

void Game::createPlayer()
{
	_player = _entityManager->addEntity<Player>("player");
	_player->processEvent();
	float x = _window->getRenderWindow().getSize().x / 2.0f;
	float y = _window->getRenderWindow().getSize().y / 2.0f;

	_player->setPosition(x,y);
	_player->setVelocity(1, 0);
}
