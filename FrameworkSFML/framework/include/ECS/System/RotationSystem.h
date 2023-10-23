#pragma once
#include "ECS/System/System.h"
#include <ECS/Component/CRotation.h>
#include <ECS/Component/CDrawable.h>

class RotationSystem :
	public BaseSystem
{
public:
	RotationSystem(){};

    void draw(sf::RenderWindow& window) override;

	void update(sf::Time deltaTime) override;
};