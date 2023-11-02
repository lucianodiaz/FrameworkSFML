#pragma once
#include <ECS/Entity/Gameplay/include/Actor.h>
#include <ECS/Component/CDrawable.h>
#include <ECS/Component/CRotation.h>
#include <ECS/Component/CProjectile.h>
#include <ECS/Component/CCollision.h>

class Meteor : public Actor
{
protected:
	float rotationSpeed{};

	float life{2};
public:

	std::shared_ptr<CDrawable>ComponentDrawable;
	std::shared_ptr<CRotation>ComponentRotation;
	std::shared_ptr<CProjectile>ComponentProjectile;
	std::shared_ptr<CCollision>ComponentCollision;

	
	Meteor(const string& tag, const size_t id);
	Meteor(const string& tag, const size_t id, Configuration::Textures tex_id, sf::Vector2f pos);

	Meteor(const string& tag, const size_t id, sf::Vector2f pos);
	virtual ~Meteor();

	virtual void update(sf::Time deltaTime) override;
	virtual void beginPlay() override;

	virtual void handleCollision(Actor& otherEntity) override;

	virtual void handleEndCollision(Actor& otherEntity) override;
};

//const int numBarrels = 19;
//const float circleRadius = 200.0f;  // Radio del círculo
//const float angleIncrement = (2 * 3.14159) / numBarrels;  // Incremento angular

//for (int i = 0; i < numBarrels; i++)
//{
//	float angle = i * angleIncrement;  // Ángulo para la posición en el círculo
//	float xPos = x + circleRadius * std::cos(angle);  // Calcular la posición x
//	float yPos = y + circleRadius * std::sin(angle);  // Calcular la posición y

//	auto barrel = world->getEntityManager()->spawnEntity<Pawn>("barrel", Configuration::Textures::Barrel, sf::Vector2f(xPos, yPos));
//	barrel->ComponentDrawable->layer = 0;
//}