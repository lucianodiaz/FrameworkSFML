#include <Game.h>

Game::Game(int x, int y) :
	_window(std::make_unique<Window>(x,y,"Tetris"))
{
}

void Game::run(int frame_per_seconds)
{
	sf::Clock clock;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Time TimerPerFrame = sf::seconds(1.f / frame_per_seconds);

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

}

void Game::draw()
{
	_window->clear();

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
