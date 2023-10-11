#include <ECS/Entity/Gameplay/include/Actor.h>

Actor::Actor(const string& tag, const size_t id) :Entity(tag, id)
{
	ComponentTransform = addComponent<CTransform>();
	beginPlay();
}

Actor::Actor(const string& tag, const size_t id, sf::Vector2f pos) :Entity(tag, id)
{
	ComponentTransform = addComponent<CTransform>(pos);
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
	return	ComponentTransform->position;
}

sf::Vector2f& Actor::getVelocity()
{
	return ComponentTransform->velocity;
}
