#include "QuadTreeLogic.h"
#include <ECS/Component/CDrawable.h>

QuadTreeLogic::QuadTreeLogic(sf::FloatRect bounds, int maxEntities): _maxEntities(maxEntities)
{
	_root = std::make_shared<QuadTreeNode>();
	_root->bounds = bounds;
}

void QuadTreeLogic::insert(shared_ptr<Actor> entity)
{
	insert(_root, entity); // Start insertion from the root node
}

void QuadTreeLogic::clear()
{
	clearNode(_root);
}

void QuadTreeLogic::clearNode(shared_ptr<QuadTreeNode> node)
{
	if (node == nullptr) return;

	for (const auto& child : node->nodes)
	{
		clearNode(child);
	}

	node->entities.clear();
}

void QuadTreeLogic::insert(shared_ptr<QuadTreeNode> node, shared_ptr<Actor> entity)
{
	// If the entity doesn't intersect with the node's bounds, return
	if (!node->bounds.intersects(entity->getComponent<CDrawable>()->sprite.getGlobalBounds()))
	{
		return;
	}

	// If the node already has child nodes, insert the entity into appropriate child node(s)
	if (node->nodes[0] != nullptr)
	{
		for (const auto& child : node->nodes)
		{
			insert(child, entity);
		}
		return;
	}

	// If the node doesn't have child nodes and hasn't reached the maximum capacity,
	// simply add the entity to its list of entities
	if (node->entities.size() < _maxEntities)
	{
		node->entities.push_back(entity);
		return;
	}

	// If the node is at capacity and doesn't have child nodes, divide it
	divide(node);

	// Reinsert the entities from the node into appropriate child nodes
	for (const auto& ent : node->entities)
	{
		for (const auto& child : node->nodes)
		{
			if (child->bounds.intersects(ent->getComponent<CDrawable>()->sprite.getGlobalBounds()))
			{
				insert(child, ent);
				break;
			}
		}
	}

	// Clear the list of entities in the current node
	node->entities.clear();
}

void QuadTreeLogic::divide(shared_ptr<QuadTreeNode> node)
{
	float subWidth = node->bounds.width / 2.0f;
	float subHeight = node->bounds.height / 2.0f;

	//create other quads
	for (int i = 0; i < 4; ++i)
	{
		node->nodes[i] = std::make_shared<QuadTreeNode>();

		node->nodes[i]->bounds.left = node->bounds.left + (i % 2) * subWidth;
		node->nodes[i]->bounds.top = node->bounds.top + (i / 2) * subHeight;
		node->nodes[i]->bounds.width = subWidth;
		node->nodes[i]->bounds.height = subHeight;
	}

	for (const auto& entity : node->entities)
	{
		for (const auto& child : node->nodes)
		{
			if (child->bounds.intersects(entity->getComponent<CDrawable>()->sprite.getGlobalBounds()))
			{
				insert(child, entity);
				break;
			}
		}
	}

	node->entities.clear();
}

unsigned int QuadTreeLogic::getQuad(shared_ptr<QuadTreeNode> node, shared_ptr<Actor> entity)
{
	for (int i = 0; i < node->nodes.size(); i++)
	{
		if (node->nodes[i]->bounds.intersects(entity->getComponent<CDrawable>()->sprite.getGlobalBounds()))
		{
			return i;
		}
	}

	return -1;
}
