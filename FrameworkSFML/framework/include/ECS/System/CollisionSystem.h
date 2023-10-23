#pragma once
#include <ECS/System/System.h>
#include <ECS/Component/CTransform.h>
#include <ECS/Component/CCollision.h>
#include <unordered_set>
#include "CollisionLogic/QuadTree.h"

class CollisionSystem : public BaseSystem
{
public:

	CollisionSystem();
	CollisionSystem(sf::FloatRect worldBounds, int maxEntitiesPerNode);
	
	void draw(sf::RenderWindow& window) override;
	void update(sf::Time deltaTime) override;


private:
	std::unordered_set<std::shared_ptr<Actor>> _currentCollision;
	std::unique_ptr<QuadTree> quadTree;
	void drawQuadTreeBounds(sf::RenderWindow& window, const std::shared_ptr<QuadTreeNode>& node);

	void checkCollision(std::shared_ptr<CTransform>transform, std::shared_ptr<CCollision> collider, shared_ptr<Actor> entity);
};