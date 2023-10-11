#pragma once
#include <memory>


class EntityBase;

class ComponentBase
{
public:
    virtual ~ComponentBase() = default;
    virtual EntityBase& getOwner() const const = 0;
    virtual void setOwner(EntityBase* e) = 0;
};

template<typename T>
class Component : public ComponentBase
{
public:
    Component() {}

    EntityBase& getOwner() const override { return *owner; }
    void setOwner(EntityBase* e) override { owner = e; }

private:
    EntityBase* owner;
};