#pragma once
#include <ECS/Entity/Entity.h>
#include <ECS/Component/CTransform.h>
#include <SFML/System/Time.hpp>

class World;

class Actor : public Entity<Actor>, public std::enable_shared_from_this<Actor>
{
private:
	sf::Time _lifespan;
protected:
	std::shared_ptr<Actor> _attachedTo;
	std::vector<std::pair<std::shared_ptr<Actor>, sf::Vector2f>> _childrens;
	void addChildren(std::shared_ptr<Actor>& child, sf::Vector2f relativePosition);
public:
	Actor(const string& tag, const size_t id);
	Actor(const string& tag, const size_t id, sf::Vector2f pos);
	virtual void update(sf::Time deltaTime);
	virtual void beginPlay();

	std::shared_ptr<Actor>& getParent();

	void attachTo(std::shared_ptr<Actor> parent);

	void attachTo(std::shared_ptr<Actor> parent,sf::Vector2f& relativePosition);

	std::vector<std::pair<std::shared_ptr<Actor>, sf::Vector2f>>& getChildren();
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

	/*How long this Actor lives before dying, 0=forever. Note this is the INITIAL value and should not be modified once play has begun. */
	float lifespan=-1;
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
