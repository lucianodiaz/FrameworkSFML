#pragma once
#include <ECS/Component/Component.h>
#include <SFML/System/Vector2.hpp>

static const sf::Vector2f UP   (0,1);
static const sf::Vector2f DOWN (0, -1);
static const sf::Vector2f LEFT(-1, 0);
static const sf::Vector2f RIGHT(1, 0);

class CRotation : public Component<CRotation>
{
public:

    sf::Vector2f direction;

    CRotation() : direction(LEFT) {} // Inicialmente apunta hacia la derecha

    explicit CRotation(const sf::Vector2f& dir)
        : direction(dir) {}
};