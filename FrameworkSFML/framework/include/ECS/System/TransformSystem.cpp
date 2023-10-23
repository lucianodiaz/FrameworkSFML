#include "TransformSystem.h"

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
}
void TransformSystem::draw(sf::RenderWindow& window)
{
}
