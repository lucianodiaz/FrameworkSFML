#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <ECS/Entity/EntityManager.h>
#include <ECS/Entity/Gameplay/include/Actor.h>
#include <ECS/System/TransformSystem.h>
#include <World.h>

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

	void createPlayer();
private:
	
	std::shared_ptr<World> world;

	std::shared_ptr<Player> _player;
};