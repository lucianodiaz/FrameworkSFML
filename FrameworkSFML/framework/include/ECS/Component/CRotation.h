#pragma once
#include <ECS/Component/Component.h>
#include <SFML/System/Vector2.hpp>

class CRotation : public Component<CRotation>
{
public:

    float addRotation{};
    float rotation{};


    CRotation() : addRotation(0) {} // Inicialmente apunta hacia la derecha

    explicit CRotation(const float& a)
        : rotation(a) {}
};