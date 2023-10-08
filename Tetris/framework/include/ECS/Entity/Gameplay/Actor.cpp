#include "Actor.h"

Actor::Actor(const string& tag, const size_t id) :Entity(tag, id)
{
	cTransform = std::make_shared<CTransform>();
	beginPlay();
}

void Actor::update(sf::Time deltaTime)
{
}

void Actor::beginPlay()
{
}

const sf::Vector2f& Actor::getPosition() const
{
	return cTransform->position;
}

const sf::Vector2f& Actor::getVelocity() const
{
	return cTransform->velocity;
}
