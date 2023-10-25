#pragma once
#include <ECS/Entity/Gameplay/include/Actor.h>
#include <Configuration/Configuration.h>
#include <ECS/Component/CDrawable.h>
#include <ECS/Component/CRotation.h>
#include <ECS/Component/CProjectile.h>
#include <ECS/Component/CCollision.h>

class Shoot : public Actor
{

private:
	std::shared_ptr<CDrawable>ComponentDrawable;
	std::shared_ptr<CRotation>ComponentRotation;
	std::shared_ptr<CProjectile>ComponentProjectile;
	std::shared_ptr<CCollision>ComponentCollision;
	sf::Vector2f _impulse;
public:
	Shoot(const string& tag, const size_t id);
	Shoot(const string& tag, const size_t id, Configuration::Textures tex_id, sf::Vector2f pos,float rot);
	Shoot(const string& tag, const size_t id, sf::Vector2f pos);

	virtual void update(sf::Time deltaTime) override;
	virtual void beginPlay() override;

	virtual void handleCollision(Entity<Actor>& otherEntity) override;

	virtual void handleEndCollision(Entity<Actor>& otherEntity) override;

	CProjectile& getComponentProjectile() { return *ComponentProjectile; }

	float velocity=500;

};