#include "ECS/Entity/EntityManager.h"
#include <ECS/Entity/Gameplay/include/Actor.h>
#include <SFML/Graphics.hpp>
#include <Window/Window.h>
#include <ECS/System/System.h>


class World
{
    World();

    std::shared_ptr<EntityManager<Actor>> _entityManager;

    std::unique_ptr<Window> _window;


    std::vector<std::unique_ptr<BaseSystem>> _systems;
public:

    static std::shared_ptr<World> getWorld()
    {
        static std::shared_ptr<World> instance = std::shared_ptr<World>(new World());
        return instance;
    }

    void CreateWindow(int width, int height, string tittle);

    std::unique_ptr<Window>& getWindow() { return _window; }

    void update(sf::Time deltaTime);

    void draw();
    
    template<typename E, typename... Args>
    shared_ptr<E> spawnEntity(const string& tag, Args&& ... args);

    std::shared_ptr<EntityManager<Actor>>& getEntityManager() { return _entityManager; };

    template<typename S, typename... Args>
    void addSystem(Args&&... args);
};

template<typename E, typename ...Args>
inline shared_ptr<E> World::spawnEntity(const string& tag, Args && ...args)
{
    return _entityManager->spawnEntity<E>(tag, std::forward<Args>(args)...);
}

template<typename S, typename ...Args>
inline void World::addSystem(Args && ...args)
{
    std::unique_ptr<S> system = std::make_unique<S>(std::forward<Args>(args)...);
    system->setEntityManager(_entityManager);
    _systems.push_back(std::move(system));
}
