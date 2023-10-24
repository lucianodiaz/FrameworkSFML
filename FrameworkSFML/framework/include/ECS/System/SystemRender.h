#pragma once
#include "System.h"
#include <ECS/Component/CDrawable.h>
#include <ECS/Component/CRotation.h>
#include <ECS/Component/CTransform.h>

class SystemRender : public BaseSystem
{
public:
    SystemRender();

    void update(sf::Time deltaTime) override;


    void draw(sf::RenderWindow& window) override;
};