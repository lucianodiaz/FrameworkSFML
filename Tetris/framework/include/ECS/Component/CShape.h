#pragma once
#include <ECS/Component/Component.h>
#include <SFML/Graphics.hpp>

class CShape :
	public Component
{
public:
	sf::CircleShape circle;

	CShape(float radius, int points, const sf::Color& fill, const sf::Color outline, float thikness) : circle(radius,points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thikness);
		circle.setOrigin(radius, radius);
	}
};