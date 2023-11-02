#include "SystemRender.h"

SystemRender::SystemRender() : BaseSystem()
{
}

void SystemRender::update(sf::Time deltaTime)
{
    // Obtener todas las entidades con componente de render
    auto entities = _entityManager->getEntitiesWithComponent<CDrawable, CTransform>();

    for (const auto& entity : entities)
    {
        auto drawable = entity->getComponent<CDrawable>();
        auto transform = entity->getComponent<CTransform>();

        drawable->sprite.setPosition(transform->position);
    }
}

void SystemRender::draw(sf::RenderWindow& window)
{

    auto entities = _entityManager->getEntitiesWithComponent<CDrawable, CTransform>();
    std::vector<std::shared_ptr<Actor>> entitiesVector(entities.begin(), entities.end());

    std::sort(entitiesVector.begin(), entitiesVector.end(), [](const std::shared_ptr<Actor>& a, const std::shared_ptr<Actor>& b) {
        return a->getComponent<CDrawable>()->layer < b->getComponent<CDrawable>()->layer;
        });


    entities.assign(entitiesVector.begin(), entitiesVector.end());

    for (const auto& entity : entities)
    {
        auto drawable = entity->getComponent<CDrawable>();
        window.draw(drawable->sprite);

        if (entity->tag() == "ship")
        {
            auto ComponentRotation = entity->getComponent<CRotation>();

            float angleInRadians = (ComponentRotation->rotation) * 3.14159265 / 180; // Convierte el ángulo a radianes
            sf::Vector2f direction(cos(angleInRadians), sin(angleInRadians));

            // Dibuja el sprite y la dirección en la que apunta
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = entity->ComponentTransform->position;
            line[1].position = entity->ComponentTransform->position + 50.f * direction; // Multiplica por una longitud deseada
            line[0].color = sf::Color::Red;
            line[1].color = sf::Color::Red;

            window.draw(line);
        }
    }

}
