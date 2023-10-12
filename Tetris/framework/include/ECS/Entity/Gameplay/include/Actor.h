#pragma once
#include <ECS/Entity/Entity.h>
#include <ECS/Component/CTransform.h>
#include <SFML/System/Time.hpp>

class Actor : public Entity<Actor>
{
public:
	Actor(const string& tag, const size_t id);
	Actor(const string& tag, const size_t id, sf::Vector2f pos);
	virtual void update(sf::Time deltaTime);
	virtual void beginPlay();


	template<typename ... Args>
	void setPosition(Args&& ... args);

	virtual sf::Vector2f& getPosition();


	template<typename ... Args>
	void setVelocity(Args&& ... args);

    sf::Vector2f& getVelocity();


	std::shared_ptr<CTransform> ComponentTransform;


	virtual void handleCollision(Entity<Actor>& otherEntity) override;
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
