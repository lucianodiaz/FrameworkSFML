#include "Shoot/Shoot.h"


Shoot::Shoot(const string& tag, const size_t id) : Actor(tag,id)
{
	ComponentDrawable = addComponent<CDrawable>();
	ComponentRotation = addComponent<CRotation>();
	beginPlay();
}

Shoot::Shoot(const string& tag, const size_t id, Configuration::Textures tex_id, sf::Vector2f pos, float rot) : Actor(tag, id,pos)
{
	ComponentDrawable = addComponent<CDrawable>(tex_id);
	ComponentRotation = addComponent<CRotation>();
	ComponentRotation->rotation = rot;
	beginPlay();
}

Shoot::Shoot(const string& tag, const size_t id, sf::Vector2f pos) : Actor(tag, id,pos)
{
	ComponentDrawable = addComponent<CDrawable>();
	ComponentRotation = addComponent<CRotation>();
	beginPlay();
}

void Shoot::beginPlay()
{
	Actor::beginPlay();

}

void Shoot::update(sf::Time deltaTime)
{
	Actor::update(deltaTime);
	float seconds = deltaTime.asSeconds();

}

void Shoot::handleCollision(Entity<Actor>& otherEntity)
{
}

void Shoot::handleEndCollision(Entity<Actor>& otherEntity)
{
}
