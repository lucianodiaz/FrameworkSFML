#pragma once
#include <ECS/System/System.h>
#include <ECS/Component/CTransform.h>
#include <ECS/Component/CCollision.h>
#include <unordered_set>
#include "QuadTree/QuadTreeLogic.h"


class CollisionSystem : public BaseSystem
{
public:

	CollisionSystem();
	CollisionSystem(sf::FloatRect worldBounds, int maxEntitiesPerNode);
	
	void draw(sf::RenderWindow& window) override;
	void update(sf::Time deltaTime) override;

	

private:

	std::unique_ptr<QuadTreeLogic> quadTree;

	std::unordered_set<std::shared_ptr<Actor>> _currentCollision;

	void performCollisionDetection(shared_ptr<QuadTreeNode> node);
	void checkCollision(shared_ptr<Actor> entity, shared_ptr<Actor> otherEntity);
};