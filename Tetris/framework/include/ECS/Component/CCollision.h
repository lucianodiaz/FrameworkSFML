#pragma once
#include <ECS/Component/Component.h>
#include <SFML/Graphics/Rect.hpp>

class CCollision : public Component<CCollision>
{
public:
	bool drawDebug = false;
	sf::FloatRect bounds;
	bool isBlocking;
	CCollision(const sf::FloatRect& bounds,bool blocking=false) :bounds(bounds),isBlocking(blocking) {}
};