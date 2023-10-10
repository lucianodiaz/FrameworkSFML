#pragma once
#include <SFML/System/Time.hpp>
class BaseSystem
{
public:
    virtual ~BaseSystem() = default;
    virtual void update(sf::Time deltaTime) = 0;
};