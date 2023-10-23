#pragma once
#include "System.h"

class SystemRender : public BaseSystem
{
public:
    SystemRender();

    void update(sf::Time deltaTime) override;


    void draw(sf::RenderWindow& window) override;
};