#pragma once
#include <ECS/Component/Component.h>
#include <SFML/System/Vector2.hpp>

class CRotation : public Component<CRotation>
{
protected:
 
public:
    float rotation{};
    //put this values on degrees
    float addRotation{};


    const float getRotation() { return rotation; }
    CRotation() : addRotation(0) {} // Inicialmente apunta hacia la derecha

    explicit CRotation(const float& a)
        : rotation(a) {}

    friend class RotationSystem;
    friend class SystemRender;
};