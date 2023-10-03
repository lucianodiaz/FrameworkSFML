#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <Window/Window.h>


class Game
{

public:

	Game(int x=1280,int y=720);

	void run(int frame_per_seconds=30);

	virtual ~Game();

protected:

	void update(sf::Time deltaTime);

	void draw();

	void processEvents();

private:

	std::unique_ptr<Window> _window;
};