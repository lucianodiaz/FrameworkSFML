#pragma once
#include <ECS/Entity/Entity.h>

class Actor : public Entity<Actor>
{
public:

	Actor(const string& tag, const size_t id);
	virtual void update(sf::Time deltaTime);
	virtual void beginPlay();

	template<typename ... Args>
	void setPosition(Args&& ... args);

	virtual const sf::Vector2f& getPosition()const;


	template<typename ... Args>
	void setVelocity(Args&& ... args);

	const sf::Vector2f& getVelocity()const;

protected:
	std::shared_ptr<CTransform> cTransform;
};

template<typename ...Args>
inline void Actor::setPosition(Args && ...args)
{
	if (cTransform)
	{
		cTransform->setPosition(std::forward<Args>(args)...);
	}
}

template<typename ...Args>
inline void Actor::setVelocity(Args && ...args)
{
	if (cTransform)
	{
		cTransform->setVelocity(std::forward<Args>(args)...);
	}
}
