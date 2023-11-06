#pragma once
#include <ECS/Component/Component.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <ECS/Entity/Gameplay/include/Actor.h>
class CCamera : public Component<CCamera>
{

public:
	CCamera()
	{

	};

	CCamera(sf::FloatRect size)
	{
		sf::View v(size);
		Camera = v;
	}
	CCamera(sf::Vector2f center, sf::Vector2f size)
	{
		sf::View v(center, size);
		Camera = v;
		Size = size;
		Center = center;
	}

	sf::View Camera{};
	sf::Vector2f Center{};
	sf::Vector2f Size{};
	sf::Vector2f Move{};
	float Zoom{1.0f};
	float Angle{0.0f};
	float LagFactor{ 1.0f };

};