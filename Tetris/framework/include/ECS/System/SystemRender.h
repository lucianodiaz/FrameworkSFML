#pragma once
#include "System.h"
#include <ECS/Component/CDrawable.h>
#include <ECS/Entity/EntityManager.h>
#include <ECS/Entity/Gameplay/Actor.h>
#include <SFML/Graphics.hpp>

class SystemRender : public BaseSystem
{
public:
    SystemRender(sf::RenderWindow& window) : _window(window) {}

    void update(sf::Time deltaTime) override
    {
        _window.clear();

        // Obtener todas las entidades con componente de render
        auto entities = _entityManager->getEntitiesWithComponent<CDrawable,CTransform>();

        for (const auto& entity : entities)
        {
            auto drawable = entity->getComponent<CDrawable>();
            auto transform = entity->getComponent<CTransform>();

            drawable->sprite.setPosition(transform->position);
            _window.draw(drawable->sprite);
        }

        _window.display();
    }

    void setEntityManager(std::shared_ptr<EntityManager<Actor>> entityManager)
    {
        _entityManager = entityManager;
    }

private:
    std::shared_ptr<EntityManager<Actor>> _entityManager;
    sf::RenderWindow& _window;
};