#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::CollisionSystem(sf::FloatRect worldBounds, int maxEntitiesPerNode)
{
	quadTree = std::make_unique<QuadTreeLogic>(worldBounds, maxEntitiesPerNode);
}

void CollisionSystem::draw(sf::RenderWindow& window)
{
	auto entities = _entityManager->getEntitiesWithComponent<CTransform, CCollision>();
	for (const auto& entity : entities)
	{
		if (entity->getComponent<CCollision>()->drawDebug)
		{
			auto transformComponent = entity->ComponentTransform;
			auto collisionComponent = entity->getComponent<CCollision>();

			sf::RectangleShape collisionShape;

			collisionShape.setSize(sf::Vector2f(collisionComponent->bounds.width, collisionComponent->bounds.height));
			collisionShape.setOutlineColor(sf::Color::Red);
			collisionShape.setOutlineThickness(1.0f);
			collisionShape.setFillColor(sf::Color::Transparent);
			collisionShape.setOrigin(collisionComponent->bounds.width / 2, collisionComponent->bounds.height / 2);
			collisionShape.setPosition(transformComponent->position.x, transformComponent->position.y);
			window.draw(collisionShape);
		}

	}
}

void CollisionSystem::update(sf::Time deltaTime)
{

	//Insert all colliders into the quad tree
	auto entitiesWithColliders = _entityManager->getEntitiesWithComponent<CTransform, CCollision>();
	for (const auto& entity : entitiesWithColliders)
	{
		quadTree->insert(entity);
	}

	performCollisionDetection(quadTree->root());

	quadTree->clear();
}

void CollisionSystem::performCollisionDetection(shared_ptr<QuadTreeNode> node)
{
	if (!node) return;

	auto entities = node->entities;

	//cout << "Quantity of entities to check collisions: " << node->entities.size() << endl;
	for (size_t i = 0; i < entities.size(); ++i)
	{
		for (size_t j = i + 1; j < entities.size(); ++j)
		{
			checkCollision(entities[i], entities[j]);
		}
	}

	// Recursively perform collision detection on child nodes
	for (const auto& child : node->nodes)
	{
		performCollisionDetection(child);
	}
}

void CollisionSystem::checkCollision(shared_ptr<Actor> entity, shared_ptr<Actor> otherEntity)
{
	auto collider = entity->getComponent<CCollision>();
	auto transform = entity->ComponentTransform;

	sf::FloatRect entityBounds = collider->bounds;

	entityBounds.left += transform->position.x;
	entityBounds.top += transform->position.y;

	std::unordered_set<std::shared_ptr<Actor>> previousCollision = _currentCollision;

	_currentCollision.clear();

		if (otherEntity != nullptr && otherEntity != entity && entity->isAlive())
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

				if (entity->onBeginCollision && otherEntity->isAlive())
				{
					entity->onBeginCollision(*otherEntity);
					
				}

				if (otherEntity->onBeginCollision && otherEntity->isAlive())
				{
					otherEntity->onBeginCollision(*entity);
					
				}

				_currentCollision.insert(otherEntity);
				_currentCollision.insert(entity);
			}
		}


	//End Collision
	for (const auto& prevEntity : previousCollision)
	{
		if (prevEntity != entity)
		{
			if (_currentCollision.find(prevEntity) == _currentCollision.end())
			{
				if (entity->onEndCollision)
				{
					entity->onEndCollision(*prevEntity);
				}

				if (prevEntity->onEndCollision)
				{
					prevEntity->onEndCollision(*entity);
				}
			}
		}

	}
}
