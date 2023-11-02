#include <ECS/Entity/Gameplay/include/Actor.h>
#include <World.h>


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
	if (initialLifespan > 0)
	{
		_lifespan += deltaTime;
		if (_lifespan >= sf::seconds(initialLifespan))
		{
			destroy();
		}
	}

}

void Actor::beginPlay()
{
	
	_lifespan = sf::Time::Zero;
	setOnBeginCollision([this](Actor& otherEntity)
		{
			this->handleCollision(otherEntity);
		});

	setOnEndCollision([this](Actor & otherEntity)
	{
			this->handleEndCollision(otherEntity);
	});
}

std::shared_ptr<Actor>& Actor::getParent()
{
	return _attachedTo;
}

void Actor::attachTo(std::shared_ptr<Actor> parent)
{
	_attachedTo = parent;
	auto l = shared_from_this();
	auto relativePosition = sf::Vector2f(0, 0);
	parent->addChildren(l, relativePosition);
}

void Actor::attachTo(std::shared_ptr<Actor> parent, sf::Vector2f& relativePosition)
{
	_attachedTo = parent;
	auto l = shared_from_this();
	parent->addChildren(l, relativePosition);
}

std::vector<std::pair<std::shared_ptr<Actor>, sf::Vector2f>>& Actor::getChildren()
{
	// // O: insert return statement here
	return _childrens;
}

void Actor::addChildren(std::shared_ptr<Actor>& child, sf::Vector2f relativePosition)
{
	_childrens.push_back(std::make_pair(child, relativePosition));
}


sf::Vector2f& Actor::getPosition()
{
	return	ComponentTransform->position;
}

sf::Vector2f Actor::getRelativePosition()
{
	// // O: insert return statement here

	if (_attachedTo)
	{
		sf::Vector2f parentPosition = _attachedTo->getPosition();
		return (parentPosition - ComponentTransform->position );
	}
	else
	{
		return ComponentTransform->position;
	}
}


sf::Vector2f& Actor::getVelocity()
{
	return ComponentTransform->offset;
}

void Actor::handleCollision(Actor& otherEntity)
{
	//std::cout << _tag << ": BeginCollision with: " << otherEntity.tag() << std::endl;
}

void Actor::handleEndCollision(Actor& otherEntity)
{
	//std::cout << _tag << ": EndCollision with: " << otherEntity.tag() << std::endl;
}

std::shared_ptr<World> Actor::getWorld()
{
	return World::getWorld();
}
