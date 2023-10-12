#pragma once
#include <ECS/System/System.h>
#include <ECS/Component/CTransform.h>
#include <ECS/Component/CCollision.h>
#include <ECS/Entity/Gameplay/include/Actor.h>
#include <ECS/Entity/EntityManager.h>

class CollisionSystem : public BaseSystem
{
public:
	void update(sf::Time deltaTime) override
	{
		auto entitiesWithColliders = _entityManager->getEntitiesWithComponent<CTransform, CCollision>();

		for (const auto& entity : entitiesWithColliders)
		{
			auto transformComponent = entity->ComponentTransform;
			auto collisionComponent = entity->getComponent<CCollision>();

			checkCollision(transformComponent, collisionComponent,entity);
		}
	}


	void setEntityManager(std::shared_ptr<EntityManager<Actor>> entityManager)
	{
		_entityManager = entityManager;
	}

private:
	std::shared_ptr<EntityManager<Actor>> _entityManager;

	void checkCollision(std::shared_ptr<CTransform>transform, std::shared_ptr<CCollision> collider,shared_ptr<Actor> entity)
	{
		sf::FloatRect entityBounds = collider->bounds;

		entityBounds.left += transform->position.x;
		entityBounds.top += transform->position.y;

		auto entitiesWithColliders = _entityManager->getEntitiesWithComponent<CTransform, CCollision>();

		for (const auto& otherEntity : entitiesWithColliders)
		{
			if (otherEntity != nullptr && otherEntity != entity)
			{
				auto otherTransform = otherEntity->ComponentTransform;
				auto otherCollider = otherEntity->getComponent<CCollision>();

				sf::FloatRect otherBound = otherCollider->bounds;

				otherBound.left += otherTransform->position.x;
				otherBound.top += otherTransform->position.y;

				if (entityBounds.intersects(otherBound))
				{
					if (otherCollider->isBlocking)
					{
						// Calcula la separación en cada eje
						float xSeparation = 0.0f;
						float ySeparation = 0.0f;

						if (entityBounds.left < otherBound.left)
							xSeparation = entityBounds.left + entityBounds.width - otherBound.left;
						else
							xSeparation = otherBound.left + otherBound.width - entityBounds.left;

						if (entityBounds.top < otherBound.top)
							ySeparation = entityBounds.top + entityBounds.height - otherBound.top;
						else
							ySeparation = otherBound.top + otherBound.height - entityBounds.top;

						// Ajusta la posición de la entidad en función de la menor separación
						if (xSeparation < ySeparation)
							transform->position.x += (entityBounds.left < otherBound.left) ? -xSeparation : xSeparation;
						else
							transform->position.y += (entityBounds.top < otherBound.top) ? -ySeparation : ySeparation;
					}

					if (entity->onBeginCollision)
					{
						entity->onBeginCollision(*otherEntity);
					}

					if (otherEntity->onBeginCollision)
					{
						otherEntity->onBeginCollision(*entity);
					}
				}
			}
			
		}
	}
};