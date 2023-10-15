#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <ECS/Entity/Gameplay/include/Actor.h>
#include <ECS/Entity/EntityManager.h>
class BaseSystem
{
protected:
    std::shared_ptr<EntityManager<Actor>> _entityManager;
public:
    virtual ~BaseSystem() = default;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window)=0;
    void setEntityManager(std::shared_ptr<EntityManager<Actor>> entityManager)
    {
        _entityManager = entityManager;
    }
};