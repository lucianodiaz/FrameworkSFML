#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <ECS/Entity/Gameplay/include/Actor.h>
#include <vector>
#include <memory>
#include <array>
#include <list>
class QuadTreeNode
{
public:
	sf::FloatRect bounds;
	std::list<std::shared_ptr<Actor>> entities;
	std::array<std::shared_ptr<QuadTreeNode>, 4> children;
};