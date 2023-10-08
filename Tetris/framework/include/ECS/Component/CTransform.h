#pragma once
#include <ECS/Component/Component.h>
#include <SFML/System/Vector2.hpp>
class CTransform :
    public Component
{
public:
    sf::Vector2f position{};
    sf::Vector2f velocity{};
    float angle = 0;

    CTransform(const sf::Vector2f& p, const sf::Vector2f& v, float a) : position(p), velocity(v), angle(a) {};
    CTransform(){};

    void setPosition(const sf::Vector2f& pos) { position = pos; };
    void setPosition(float x, float y) { position.x = x; position.y = y; };

    void setVelocity(const sf::Vector2f& vel) { velocity = vel; };
    void setVelocity(float x, float y) { velocity.x = x; velocity.y = y; };
};

