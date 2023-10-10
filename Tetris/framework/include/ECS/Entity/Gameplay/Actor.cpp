#include "ECS/Entity/Gameplay/Actor.h"

Actor::Actor(const string& tag, const size_t id) :Entity(tag, id)
{
	//cTransform = std::make_shared<CTransform>();
	addComponent<CTransform>();
	beginPlay();
}

void Actor::update(sf::Time deltaTime)
{
}

void Actor::beginPlay()
{
}

sf::Vector2f& Actor::getPosition()
{
	return	getComponent<CTransform>()->position;
}

sf::Vector2f& Actor::getVelocity()
{
	//return cTransform->velocity;
	return getComponent<CTransform>()->velocity;
}
