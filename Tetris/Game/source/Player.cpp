#include "Player.h"

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
}

void Player::setupInput()
{
	Character::setupInput();


	bind(Configuration::PlayerInputs::Up, [this](const sf::Event&)
		{
			sf::Vector2f UP(0, -1);

			setVelocity(100 * UP.x, 100 * UP.y);

		});

	bind(Configuration::PlayerInputs::Down, [this](const sf::Event&)
		{
			sf::Vector2f DOWN(0, 1);

			setVelocity(100 * DOWN.x, 100 * DOWN.y);

		});

	bind(Configuration::PlayerInputs::Left, [this](const sf::Event&)
		{
			sf::Vector2f LEFT(-1, 0);

			setVelocity(100 * LEFT.x, 100 * LEFT.y);

		});

	bind(Configuration::PlayerInputs::Right, [this](const sf::Event&)
		{
			sf::Vector2f RIGHT(1, 0);

			setVelocity(100 * RIGHT.x, 100 * RIGHT.y);

		});
}

void Player::handleCollision(Entity<Actor>& otherEntity)
{
	Character::handleCollision(otherEntity);
	if (otherEntity.tag() == "barrel")
	{
		otherEntity.destroy();
	}
}
