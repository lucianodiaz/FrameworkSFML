#include "RotationSystem.h"

void RotationSystem::draw(sf::RenderWindow& window)
{
}

void RotationSystem::update(sf::Time deltaTime)
{
    float seconds = deltaTime.asSeconds();

    auto entitiesWithRotator = _entityManager->getEntitiesWithComponent<CDrawable, CRotation>();
    for (const auto& entity : entitiesWithRotator)
    {
        auto drawComponent = entity->getComponent<CDrawable>();
        auto rotationComponent = entity->getComponent<CRotation>();

        //// Update rotation based on the direction vector
        //float angle = std::atan2(rotationComponent->direction.y, rotationComponent->direction.x);
        //angle = angle * 180.0f / 3.14159265f; // Convert radians to degrees
        ////drawComponent->sprite.setRotation(angle);
        drawComponent->sprite.setRotation(rotationComponent->rotation);
        float angle = rotationComponent->addRotation * 180 * seconds;
        drawComponent->sprite.rotate(angle);
        rotationComponent->rotation = drawComponent->sprite.getRotation();
        rotationComponent->addRotation = 0;
    }

}
