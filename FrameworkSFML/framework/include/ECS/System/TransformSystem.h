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
        // Aquí procesamos las transformaciones para cada entidad
        // Por ejemplo, actualizamos la posición en base a la velocidad

        // Obtener todas las entidades con componente de transformación
        auto entities = _entityManager->getEntitiesWithComponent<CTransform>();

        for (auto& entity : entities)
        {
            auto transform = entity->getComponent<CTransform>();
            // Actualizar la posición basada en la velocidad
            if (entity->getParent())
            {
                auto parentTransform = entity->getParent()->getComponent<CTransform>();
                if (parentTransform)
                {
                    // Calcula la nueva posición en relación con el padre
                    sf::Vector2f relativePosition = entity->getRelativePosition();
                    sf::Vector2f newPosition = parentTransform->position + relativePosition;
                    transform->position = newPosition;
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