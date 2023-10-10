#pragma once

class ComponentBase
{
public:
    virtual ~ComponentBase() = default;
};

template<typename T>
class Component : public ComponentBase
{
public:
    Component() {}
};