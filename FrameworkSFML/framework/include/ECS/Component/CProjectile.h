#pragma once
#include "Component.h"
#include <SFML/System/Vector2.hpp>

class CProjectile : public Component<CProjectile>
{
public:
	sf::Vector2f direction;
	float speed;

	CProjectile();
	CProjectile(const sf::Vector2f& dir, float spd) 
		: direction(dir), speed(spd){};


};