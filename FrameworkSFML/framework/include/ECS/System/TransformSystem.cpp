#include "TransformSystem.h"
#include <ECS/Component/CProjectile.h>

TransformSystem::TransformSystem()
{
}
void TransformSystem::update(sf::Time deltaTime)
{
    // Obtener todas las entidades con componente de transformaci�n
    auto entities = _entityManager->getEntitiesWithComponent<CTransform>();

    for (auto& entity : entities)
    {
        auto transform = entity->getComponent<CTransform>();
        if (entity->getParent())
        {
            auto parentTransform = entity->getParent()->getComponent<CTransform>();
            if (parentTransform)
            {
                // Buscar la posici�n relativa del hijo
                for (const auto& childData : entity->getParent()->getChildren())
                {
                    if (childData.first == entity)
                    {
                        // Calcular la nueva posici�n en relaci�n con el padre
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

    auto entitiesWithProjectile = _entityManager->getEntitiesWithComponent<CProjectile>();

    for (auto& entity : entitiesWithProjectile)
    {
        auto transform = entity->getComponent<CTransform>();
        auto projectile = entity->getComponent<CProjectile>();

        // Actualizar la posici�n de la bala en funci�n de su velocidad y direcci�n
        transform->position.x += projectile->direction.x * projectile->speed * deltaTime.asSeconds();
        transform->position.y += projectile->direction.y * projectile->speed * deltaTime.asSeconds();
    }
}
void TransformSystem::draw(sf::RenderWindow& window)
{
}
