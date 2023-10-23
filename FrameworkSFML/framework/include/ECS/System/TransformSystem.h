#pragma once
#include <ECS/System/System.h>
#include <ECS/Component/CTransform.h>
#include <memory>
#include <iostream>
class TransformSystem : public BaseSystem
{
public:
    TransformSystem();

    void update(sf::Time deltaTime) override;

    void draw(sf::RenderWindow& window) override;
};