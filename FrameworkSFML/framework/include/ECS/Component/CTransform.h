#pragma once
#include <ECS/Component/Component.h>
#include <SFML/System/Vector2.hpp>
class CTransform :
    public Component<CTransform>
{
public:
    sf::Vector2f position{};
    sf::Vector2f offset{};

    CTransform(const sf::Vector2f& p, const sf::Vector2f& v) : position(p), offset(v){};
    CTransform(const sf::Vector2f& p) : position(p) {};
    CTransform(){};

    void setPosition(const sf::Vector2f& pos) { position = pos; };
    void setPosition(float x, float y) { position.x = x; position.y = y; };

    void setVelocity(const sf::Vector2f& vel) { offset = vel; };
    void setVelocity(float x, float y) { offset.x = x; offset.y = y; };
};

