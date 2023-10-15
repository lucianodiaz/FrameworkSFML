#include "Player.h"
#include "World.h"


Player::Player(const string& tag, const size_t id) : Character(tag, id)
{
	beginPlay();
}

Player::Player(const string& tag, const size_t id, Configuration::Textures tex_id, sf::Vector2f pos) : Character(tag, id, tex_id, pos)
{
	beginPlay();
}

Player::Player(const string& tag, const size_t id, sf::Vector2f pos) : Character(tag, id, pos)
{
	beginPlay();
}


void Player::update(sf::Time deltaTime)
{
	Character::update(deltaTime);

	float seconds = deltaTime.asSeconds();

	_timeSinceLastSpawn += deltaTime;
}

void Player::beginPlay()
{
	Character::beginPlay();
	setupInput();
}

void Player::processEvent()
{
	setVelocity(0, 0);
	ActionTarget::processEvents();
	/*isPressed = false;*/
}

void Player::setupInput()
{
	Character::setupInput();


	bind(Configuration::PlayerInputs::Up, [this](const sf::Event&)
		{
			sf::Vector2f UP(0, -1);

			setVelocity(500 * UP.x, 500 * UP.y);

		});

	bind(Configuration::PlayerInputs::Down, [this](const sf::Event&)
		{
			sf::Vector2f DOWN(0, 1);

			setVelocity(500 * DOWN.x, 500 * DOWN.y);

		});

	bind(Configuration::PlayerInputs::Left, [this](const sf::Event&)
		{
			sf::Vector2f LEFT(-1, 0);

			setVelocity(500 * LEFT.x, 500 * LEFT.y);

		});

	bind(Configuration::PlayerInputs::Right, [this](const sf::Event&)
		{
			sf::Vector2f RIGHT(1, 0);

			setVelocity(500 * RIGHT.x, 500 * RIGHT.y);

		});

	bind(Configuration::PlayerInputs::LeftClick, [this](const sf::Event&)
		{
			//spawn();
		});
}
void Player::spawn()
{
	if (_timeSinceLastSpawn > sf::seconds(0.3))
	{
		auto mousePos = sf::Mouse::getPosition(getWorld()->getWindow()->getRenderWindow());
		auto mouseCoord = getWorld()->getWindow()->getRenderWindow().mapPixelToCoords(mousePos);

		getWorld()->spawnEntity<Pawn>("barrel", Configuration::Textures::Barrel, sf::Vector2f(mouseCoord.x, mouseCoord.y));
		_timeSinceLastSpawn = sf::Time::Zero;
	}
	
}

void Player::handleCollision(Entity<Actor>& otherEntity)
{
	Character::handleCollision(otherEntity);
}

void Player::handleEndCollision(Entity<Actor>& otherEntity)
{
	Character::handleEndCollision(otherEntity);
}
