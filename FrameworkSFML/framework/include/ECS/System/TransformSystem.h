#pragma once
#include <ECS/System/System.h>
#include <ECS/Component/CTransform.h>
#include <memory>
#include <iostream>
class TransformSystem : public BaseSystem
{
public:
    void update(sf::Time deltaTime) override
    {
        // Obtener todas las entidades con componente de transformación
        auto entities = _entityManager->getEntitiesWithComponent<CTransform>();

        for (auto& entity : entities)
        {
            auto transform = entity->getComponent<CTransform>();
            if (entity->getParent())
            {
                auto parentTransform = entity->getParent()->getComponent<CTransform>();
                if (parentTransform)
                {
                    // Buscar la posición relativa del hijo
                    for (const auto& childData : entity->getParent()->getChildren())
                    {
                        if (childData.first == entity)
                        {
                            // Calcular la nueva posición en relación con el padre
                            sf::Vector2f relativePosition = childData.second;
                            sf::Vector2f newPosition = parentTransform->position + relativePosition;
                            transform->position = newPosition;
                            break;
                        }
                    }
                }
            }
            else
            {
                transform->position += transform->offset;
            }
        }
    }
    void draw(sf::RenderWindow& window) override {}
};