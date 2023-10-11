#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <Window/Window.h>
#include <Player.h>
#include <ECS/Entity/EntityManager.h>
#include <ECS/Entity/Gameplay/Actor.h>
#include <ECS/System/TransformSystem.h>

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

	std::unique_ptr<Window> _window;

	std::shared_ptr<Player> _player;

	std::shared_ptr<EntityManager<Actor>> _entityManager;

	std::vector<std::unique_ptr<BaseSystem>> _systems;
};