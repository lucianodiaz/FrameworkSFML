#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <memory>
#include <typeinfo>
#include <any>
#include <exception>
#include <ECS/Component/Component.h>

using std::string;

class EntityBase
{
protected:
    string _tag{ "default" };
    bool _alive = true;
    size_t _id = 0;
  
public:
    EntityBase(const string& tag, const size_t id) :_tag(tag), _id(id)
    {
    }
    virtual ~EntityBase() = default;
};


template<typename ENTITY>
class Entity : public EntityBase
{
protected:

    template<typename> friend class EntityManager;
    Entity(const string& tag, const size_t id) : EntityBase(tag,id)
    {
    }
 
    std::unordered_map<string, std::shared_ptr<ComponentBase>> _components;

    template<typename COMPONENT, typename... Args>
    std::shared_ptr<COMPONENT> addComponent(Args&&... args);

    template<typename COMPONENT>
    void removeComponent();

    using CollisionEventFunction = std::function<void(Entity<ENTITY>& other)>;

public:

    virtual ~Entity(){};
    void destroy() { _alive = false; };
    bool isAlive() const { return _alive; }
    const string& tag() const { return _tag; }
    const size_t id() const { return _id; }

    template<typename COMPONENT>
    std::shared_ptr<COMPONENT> getComponent();

    template<typename COMPONENT>
    bool hasComponent() const;



    void setOnBeginCollision(CollisionEventFunction eventCol);
    void setOnEndCollision(CollisionEventFunction eventCol);

    virtual void handleCollision(Entity<ENTITY>& otherEntity);
    virtual void handleEndCollision(Entity<ENTITY>& otherEntity);

    CollisionEventFunction onBeginCollision;
    CollisionEventFunction onEndCollision;

};

template<typename ENTITY>
template<typename COMPONENT, typename ...Args>
inline std::shared_ptr<COMPONENT> Entity<ENTITY>::addComponent(Args&&... args)
{
    auto c = std::make_shared<COMPONENT>(std::forward<Args>(args)...);
    c->setOwner(reinterpret_cast<EntityBase*>(this));
    _components[typeid(COMPONENT).name()] = c;
   
    return c;
}

template<typename ENTITY>
template<typename COMPONENT>
inline std::shared_ptr<COMPONENT> Entity<ENTITY>::getComponent()
{
    auto it = _components.find(typeid(COMPONENT).name());

    if (it != _components.end())
    {
        auto component = std::dynamic_pointer_cast<COMPONENT>(it->second);
        if (component)
        {
            return component;
        }
    }
    return nullptr;
}

template<typename ENTITY>
template<typename COMPONENT>
inline bool Entity<ENTITY>::hasComponent() const
{
    auto it = _components.find(typeid(COMPONENT).name());

    return it != _components.end();
}

template<typename ENTITY>
template<typename COMPONENT>
inline void Entity<ENTITY>::removeComponent()
{
	auto it = _components.find(typeid(COMPONENT).name());

	if (it != _components.end()) 
    {
		_components.erase(it);
	}
}

template<typename ENTITY>
inline void Entity<ENTITY>::setOnBeginCollision(CollisionEventFunction eventCol)
{
    onBeginCollision = eventCol;
}

template<typename ENTITY>
inline void Entity<ENTITY>::setOnEndCollision(CollisionEventFunction eventCol)
{
    onEndCollision = eventCol;
}

template<typename ENTITY>
inline void Entity<ENTITY>::handleCollision(Entity<ENTITY>& otherEntity)
{
}

template<typename ENTITY>
inline void Entity<ENTITY>::handleEndCollision(Entity<ENTITY>& otherEntity)
{
}
