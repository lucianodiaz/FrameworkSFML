#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::CollisionSystem(sf::FloatRect worldBounds, int maxEntitiesPerNode)
{
	quadTree = std::make_unique<QuadTree>(worldBounds, maxEntitiesPerNode);
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
	drawQuadTreeBounds(window, quadTree->_root);
}

void CollisionSystem::update(sf::Time deltaTime)
{
	auto entitiesWithColliders = _entityManager->getEntitiesWithComponent<CTransform, CCollision>();
	quadTree->update();
	for (const auto& entity : entitiesWithColliders)
	{

		auto transformComponent = entity->ComponentTransform;
		auto collisionComponent = entity->getComponent<CCollision>();
		quadTree->insert(entity);
		checkCollision(transformComponent, collisionComponent, entity);
	}
	quadTree->clear();
}

void CollisionSystem::drawQuadTreeBounds(sf::RenderWindow& window, const std::shared_ptr<QuadTreeNode>& node)
{
	if (node == nullptr)
		return;

	sf::RectangleShape quadBounds;
	quadBounds.setPosition(sf::Vector2f(node->bounds.left, node->bounds.top));
	quadBounds.setSize(sf::Vector2f(node->bounds.width, node->bounds.height));
	quadBounds.setOutlineColor(sf::Color::Blue);
	quadBounds.setOutlineThickness(1.0f);
	quadBounds.setFillColor(sf::Color::Transparent);

	window.draw(quadBounds);

	for (const auto& child : node->children)
	{
		if (child != nullptr)
		{
			drawQuadTreeBounds(window, child);

			// Draw lines to connect the parent node to its children
			sf::Vector2f parentCenter(node->bounds.left + node->bounds.width / 2.0f,
				node->bounds.top + node->bounds.height / 2.0f);
			sf::Vector2f childCenter(child->bounds.left + child->bounds.width / 2.0f,
				child->bounds.top + child->bounds.height / 2.0f);

			sf::Vertex line[] =
			{
				sf::Vertex(parentCenter, sf::Color::Blue),
				sf::Vertex(childCenter, sf::Color::Blue)
			};

			window.draw(line, 2, sf::Lines);
		}
	}
}

void CollisionSystem::checkCollision(std::shared_ptr<CTransform> transform, std::shared_ptr<CCollision> collider, shared_ptr<Actor> entity)
{
	sf::FloatRect entityBounds = collider->bounds;

	entityBounds.left += transform->position.x;
	entityBounds.top += transform->position.y;

	//auto entitiesWithColliders = _entityManager->getEntitiesWithComponent<CTransform, CCollision>();

	std::unordered_set<std::shared_ptr<Actor>> previousCollision = _currentCollision;

	_currentCollision.clear();

	std::vector<std::shared_ptr<Actor>> posibleCollisions;
	quadTree->retrieve(posibleCollisions, entity);

	/*if (entity->tag() == "player")
	{
		std::cout << "Posible collisions: " << posibleCollisions.size() << std::endl;
	}*/


	for (const auto& otherEntity : posibleCollisions)
	{
		if (otherEntity != nullptr && otherEntity != entity && entity->isAlive())
		{
			auto otherTransform = otherEntity->ComponentTransform;
			auto otherCollider = otherEntity->getComponent<CCollision>();

			sf::FloatRect otherBound = otherCollider->bounds;

			otherBound.left += otherTransform->position.x;
			otherBound.top += otherTransform->position.y;

			quadTree->update();
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
