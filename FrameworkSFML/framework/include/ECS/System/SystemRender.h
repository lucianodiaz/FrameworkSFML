#pragma once
#include "System.h"
#include <ECS/Component/CDrawable.h>
#include <SFML/Graphics.hpp>

class SystemRender : public BaseSystem
{
public:
    SystemRender(){};

    void update(sf::Time deltaTime) override
    {
        // Obtener todas las entidades con componente de render
        auto entities = _entityManager->getEntitiesWithComponent<CDrawable,CTransform>();

        for (const auto& entity : entities)
        {
            auto drawable = entity->getComponent<CDrawable>();
            auto transform = entity->getComponent<CTransform>();

            drawable->sprite.setPosition(transform->position);
        }
    }


    void draw(sf::RenderWindow& window) override 
    {
        auto entities = _entityManager->getEntitiesWithComponent<CDrawable, CTransform>();
        std::vector<std::shared_ptr<Actor>> entitiesVector(entities.begin(), entities.end());

        std::sort(entitiesVector.begin(), entitiesVector.end(), [](const std::shared_ptr<Actor>& a, const std::shared_ptr<Actor>& b) {
            return a->getComponent<CDrawable>()->layer < b->getComponent<CDrawable>()->layer;
            });


        entities.assign(entitiesVector.begin(), entitiesVector.end());

        for (const auto& entity : entities)
        {
            auto drawable = entity->getComponent<CDrawable>();
            window.draw(drawable->sprite);
        }

    }
};