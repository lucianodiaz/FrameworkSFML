#pragma once
#include "ECS/System/System.h"
#include <ECS/Component/CRotation.h>
#include <ECS/Component/CDrawable.h>

class RotationSystem :
	public BaseSystem
{
public:
	RotationSystem(){};

	void draw(sf::RenderWindow& window) override
	{

	}

	void update(sf::Time deltaTime) override
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
            //rotationComponent->rotation = 0;
        }
		
	}
};