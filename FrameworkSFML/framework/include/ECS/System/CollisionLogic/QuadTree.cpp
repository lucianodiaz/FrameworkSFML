#include "QuadTree.h"
#include <ECS/Component/CDrawable.h>
#include <iostream>

QuadTree::QuadTree(sf::FloatRect bounds, int maxEntitiesPerNode) : _maxEntitiesPerNode(maxEntitiesPerNode)
{
    _root = std::make_shared<QuadTreeNode>();
    _root->bounds = bounds;
}

void QuadTree::clear()
{
    merge(_root);
}

void QuadTree::insert(const std::shared_ptr<Actor>& entity)
{
    // Inserta una entidad en el árbol
    if (contains(_root, entity))
        return;

    // Subdivide si es necesario
    if (_root->children[0] == nullptr && _root->entities.size() >= _maxEntitiesPerNode)
        subdivide(_root);

    // Inserta en los hijos si es posible
    for (const auto& child : _root->children)
    {
        if (child != nullptr && child->bounds.intersects(entity->getComponent<CDrawable>()->sprite.getGlobalBounds()))
        {
            insert(child, entity);
            return;
        }
    }

    // Añade la entidad al nodo actual

    _root->entities.push_back(entity);
}

void QuadTree::update()
{
    // Actualiza el árbol, redistribuyendo las entidades
    std::vector<std::shared_ptr<Actor>> allEntities;
    retrieve(allEntities, _root,nullptr);

   /* _root->entities.remove_if([](const std::shared_ptr<Actor>& entity) {
        return !entity->isAlive();
        });*/
    clear();

    for (const auto& entity : allEntities)
        insert(entity);
}

void QuadTree::retrieve(std::vector<std::shared_ptr<Actor>>& result, std::shared_ptr<Actor> entity)
{
    retrieve(result, _root, entity);
}

void QuadTree::subdivide(std::shared_ptr<QuadTreeNode> node)
{
    float subWidth = node->bounds.width / 2.0f;
    float subHeight = node->bounds.height / 2.0f;

    for (int i = 0; i < 4; ++i)
    {
        node->children[i] = std::make_shared<QuadTreeNode>();

        node->children[i]->bounds.left = node->bounds.left + (i % 2) * subWidth;
        node->children[i]->bounds.top = node->bounds.top + (i / 2) * subHeight;
        node->children[i]->bounds.width = subWidth;
        node->children[i]->bounds.height = subHeight;
    }

    // Mover entidades al nodo hijo apropiado
    std::vector<std::shared_ptr<Actor>> entitiesToMove;
    entitiesToMove.swap(node->entities);

    for (const auto& entity : entitiesToMove)
    {
        //std::cout << "Se inserto en el cuadrante: " << getQuadrant(node, entity) << std::endl;
        insert(node->children[getQuadrant(node, entity)], entity);
    }
        
}

bool QuadTree::contains(std::shared_ptr<QuadTreeNode> node, std::shared_ptr<Actor> entity)
{
    // Verifica si el nodo contiene la entidad
    return std::find(node->entities.begin(), node->entities.end(), entity) != node->entities.end();
}

void QuadTree::merge(std::shared_ptr<QuadTreeNode> node)
{
    for (int i = 0; i < 4; ++i)
    {
        if (node->children[i] != nullptr)
        {
            merge(node->children[i]);
            for (const auto& childEntity : node->children[i]->entities)
            {
                insert(node, childEntity);
            }
            node->children[i].reset();
        }
    }
}

void QuadTree::insert(const std::shared_ptr<QuadTreeNode>& node, const std::shared_ptr<Actor>& entity)
{
    // Inserta una entidad en el árbol
    if (contains(node, entity))
        return;

    // Subdivide si es necesario
    if (node->children[0] == nullptr && node->entities.size() >= _maxEntitiesPerNode)
        subdivide(node);

    // Inserta en los hijos si es posible
    for (const auto& child : node->children)
    {
        if (child != nullptr)
        {
            if(child->bounds.intersects(entity->getComponent<CDrawable>()->sprite.getGlobalBounds()))
            insert(child, entity);
            return;
        }
    }

    // Añade la entidad al nodo actual
    node->entities.push_back(entity);
}

void QuadTree::retrieve(std::vector<std::shared_ptr<Actor>>& result, std::shared_ptr<QuadTreeNode> node, std::shared_ptr<Actor> entity)
{
    // Obtiene entidades que podrían colisionar con la entidad dada
    for (const auto& child : node->children)
    {
        if (child != nullptr && entity!=nullptr && child->bounds.intersects(entity->getComponent<CDrawable>()->sprite.getLocalBounds()))
            retrieve(result, child, entity);
    }
    if(entity && entity->isAlive())
    result.insert(result.end(), node->entities.begin(), node->entities.end());
}

int QuadTree::getQuadrant(std::shared_ptr<QuadTreeNode> node, std::shared_ptr<Actor> entity)
{
    sf::FloatRect entityBounds = entity->getComponent<CDrawable>()->sprite.getGlobalBounds();

    float verticalMidpoint = node->bounds.left + node->bounds.width / 2.0f;
    float horizontalMidpoint = node->bounds.top + node->bounds.height / 2.0f;

    if (entityBounds.top < horizontalMidpoint)
    {
        if (entityBounds.left < verticalMidpoint)
            return 1;  // Top-left quadrant
        else
            return 0;  // Top-right quadrant
    }
    else
    {
        if (entityBounds.left < verticalMidpoint)
            return 2;  // Bottom-left quadrant
        else
            return 3;  // Bottom-right quadrant
    }
}