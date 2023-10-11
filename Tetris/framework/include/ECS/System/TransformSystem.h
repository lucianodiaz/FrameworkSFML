#pragma once
#include <ECS/System/System.h>
#include <ECS/Component/CTransform.h>
#include <memory>
#include <ECS/Entity/EntityManager.h>
#include <ECS/Entity/Gameplay/include/Actor.h>
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
            transform->position += transform->velocity * deltaTime.asSeconds();
        }
    }

    void setEntityManager(std::shared_ptr<EntityManager<Actor>> entityManager)
    {
        _entityManager = entityManager;
    }

private:
    std::shared_ptr<EntityManager<Actor>> _entityManager;
};