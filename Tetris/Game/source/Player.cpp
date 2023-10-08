#include "Player.h"

Player::Player(const string& tag, const size_t id) : Actor(tag,id)
{
	beginPlay();
}

void Player::update(sf::Time deltaTime)
{

	cTransform->position.x += cTransform->velocity.x;
	cTransform->position.y += cTransform->velocity.y;

	cDrawable->sprite.setPosition(cTransform->position);
}

void Player::beginPlay()
{
	Actor::beginPlay();
	cDrawable = std::make_shared<CDrawable>(Configuration::Textures::Barrel);
}

void Player::processEvent()
{
	
}
