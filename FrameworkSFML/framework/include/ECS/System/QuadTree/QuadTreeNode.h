#pragma once

#include <array>
#include <memory>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <ECS/Entity/Gameplay/include/Actor.h>


using std::vector;
using std::shared_ptr;


class QuadTreeNode
{
public:
	sf::FloatRect bounds;
	vector<shared_ptr<Actor>> entities;
	std::array<shared_ptr <QuadTreeNode>,4> nodes;
};