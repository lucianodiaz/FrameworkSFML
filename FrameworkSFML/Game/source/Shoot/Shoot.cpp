#include "Shoot/Shoot.h"


Shoot::~Shoot()
{
}

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
	initialLifespan = 1;
	ComponentCollision = addComponent<CCollision>(ComponentDrawable->sprite.getGlobalBounds());
	float rotationInRadians = ComponentRotation->rotation * 3.14159 / 180.0;
	auto dirX = std::cos(rotationInRadians);
	auto dirY = std::sin(rotationInRadians);

	float length = sqrt(dirX * dirX + dirY * dirY);
	if (length != 0) {
		dirX  /= length;
		dirY /= length;
	}
	sf::Vector2f direction = sf::Vector2f(dirX, dirY);

	ComponentProjectile = addComponent<CProjectile>(direction,velocity);

}

void Shoot::update(sf::Time deltaTime)
{
	Actor::update(deltaTime);
	float seconds = deltaTime.asSeconds();

}

void Shoot::handleCollision(Entity<Actor>& otherEntity)
{
	if (otherEntity.tag() != "Shoot" && otherEntity.tag() != _owner->tag())
	{
		destroy();
	}
	
}

void Shoot::handleEndCollision(Entity<Actor>& otherEntity)
{
}
