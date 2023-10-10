#include "Player.h"

Player::Player(const string& tag, const size_t id) : Actor(tag,id),
ActionTarget(Configuration::playerInputs)
{
	beginPlay();
	addComponent<CDrawable>(Configuration::Textures::Barrel);

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

void Player::update(sf::Time deltaTime)
{	
	/*if (hasComponent<CDrawable>())
	{
		getComponent<CDrawable>()->sprite.setPosition(getComponent<CTransform>()->position);
	}*/
}

void Player::beginPlay()
{
	Actor::beginPlay();
	
	//removeComponent<CDrawable>();
}

void Player::processEvent()
{
	setVelocity(0,0);
	ActionTarget::processEvents();
}
