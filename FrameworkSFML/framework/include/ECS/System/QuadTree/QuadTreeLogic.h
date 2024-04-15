#pragma once
#include "QuadTreeNode.h"

class QuadTreeLogic
{
public:

	QuadTreeLogic(sf::FloatRect bounds, int maxEntities);


	void insert(shared_ptr<Actor> entity);

	void clear();

	shared_ptr<QuadTreeNode> root() { return _root; }

private:

	void clearNode(shared_ptr<QuadTreeNode> node);
	void insert(shared_ptr<QuadTreeNode> node, shared_ptr<Actor> entity);
	void divide(shared_ptr<QuadTreeNode> root);

	unsigned int getQuad(shared_ptr<QuadTreeNode> node, shared_ptr<Actor> entity);
	unsigned int _maxEntities;
	shared_ptr<QuadTreeNode> _root;
};