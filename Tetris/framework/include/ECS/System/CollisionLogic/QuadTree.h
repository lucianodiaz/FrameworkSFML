#pragma once
#include "QuadTreeNode.h"

class QuadTree
{
public:
	QuadTree(sf::FloatRect bounds, int maxEntitiesPerNode);
	QuadTree() = default;

	void clear();
	void insert(const std::shared_ptr<Actor>& entity);
	void insert(const std::shared_ptr<QuadTreeNode>& node, const std::shared_ptr<Actor>& entity);
	void update();
	void retrieve(std::vector<std::shared_ptr<Actor>>& result, std::shared_ptr<Actor> entity);
	void retrieve(std::vector<std::shared_ptr<Actor>>& result, std::shared_ptr<QuadTreeNode> node, std::shared_ptr<Actor> entity);

	int getQuadrant(std::shared_ptr<QuadTreeNode> node, std::shared_ptr<Actor> entity);

	std::shared_ptr<QuadTreeNode> _root;
private:
	void subdivide(std::shared_ptr<QuadTreeNode> node);
	bool contains(std::shared_ptr<QuadTreeNode> node, std::shared_ptr<Actor> entity);
	void merge(std::shared_ptr<QuadTreeNode> node);

	
	int _maxEntitiesPerNode;
};