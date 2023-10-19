#pragma once
#include <ECS/Entity/Entity.h>
#include <ECS/Component/CTransform.h>
#include <SFML/System/Time.hpp>

class World;

class Actor : public Entity<Actor>, public std::enable_shared_from_this<Actor>
{

protected:
	std::shared_ptr<Actor> _attachedTo;
	std::vector<std::shared_ptr<Actor>> _childrens;

	void addChildren(std::shared_ptr<Actor>& children);
public:
	Actor(const string& tag, const size_t id);
	Actor(const string& tag, const size_t id, sf::Vector2f pos);
	virtual void update(sf::Time deltaTime);
	virtual void beginPlay();

	std::shared_ptr<Actor>& getParent();

	void attachTo(std::shared_ptr<Actor> parent);

	template<typename ... Args>
	void setPosition(Args&& ... args);

	virtual sf::Vector2f& getPosition();

	sf::Vector2f getRelativePosition();

	template<typename ... Args>
	void setVelocity(Args&& ... args);

    sf::Vector2f& getVelocity();


	std::shared_ptr<CTransform> ComponentTransform;


	virtual void handleCollision(Entity<Actor>& otherEntity) override;
	virtual void handleEndCollision(Entity<Actor>& otherEntity) override;

	std::shared_ptr<World> getWorld();
};

template<typename ...Args>
inline void Actor::setPosition(Args && ...args)
{
	if (ComponentTransform)
	{
		ComponentTransform->setPosition(std::forward<Args>(args)...);
	}
}

template<typename ...Args>
inline void Actor::setVelocity(Args && ...args)
{
	if (ComponentTransform)
	{
		ComponentTransform->setVelocity(std::forward<Args>(args)...);
	}
}
