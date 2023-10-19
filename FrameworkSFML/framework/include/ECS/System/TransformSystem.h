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
        // Aqu� procesamos las transformaciones para cada entidad
        // Por ejemplo, actualizamos la posici�n en base a la velocidad

        // Obtener todas las entidades con componente de transformaci�n
        auto entities = _entityManager->getEntitiesWithComponent<CTransform>();

        for (auto& entity : entities)
        {
            auto transform = entity->getComponent<CTransform>();
            // Actualizar la posici�n basada en la velocidad
            if (entity->getParent())
            {
                auto parentTransform = entity->getParent()->getComponent<CTransform>();
                if (parentTransform)
                {
                    // Calcula la nueva posici�n en relaci�n con el padre
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