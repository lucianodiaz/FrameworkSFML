#include <ECS/Entity/Gameplay/include/Actor.h>
#include <iostream>
#include <World.h>
#include <ECS/Entity/Entity.h>


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
	setOnBeginCollision([this](Entity<Actor>& otherEntity)
		{
			this->handleCollision(otherEntity);
		});

	setOnEndCollision([this](Entity<Actor> & otherEntity)
	{
			this->handleEndCollision(otherEntity);
	});
}

sf::Vector2f& Actor::getPosition()
{
	return	ComponentTransform->position;
}

sf::Vector2f& Actor::getVelocity()
{
	return ComponentTransform->velocity;
}

void Actor::handleCollision(Entity<Actor>& otherEntity)
{
	//std::cout << _tag << ": BeginCollision with: " << otherEntity.tag() << std::endl;
}

void Actor::handleEndCollision(Entity<Actor>& otherEntity)
{
	//std::cout << _tag << ": EndCollision with: " << otherEntity.tag() << std::endl;
}

std::shared_ptr<World> Actor::getWorld()
{
	return World::getWorld();
}
