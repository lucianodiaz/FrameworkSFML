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
            transform->position += transform->velocity * deltaTime.asSeconds();
        }
    }
    void draw(sf::RenderWindow& window) override {}
};