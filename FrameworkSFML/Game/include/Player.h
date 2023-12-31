#pragma once
#include <memory>
#include <Input/ActionTarget.h>
#include <ECS/Entity/Gameplay/include/Character.h>
#include <ECS/Component/CRotation.h>
#include <ECS/Component/CCamera.h>
class Player : public Character
{
	bool isPressed = false;
	bool _isMoving;
	sf::Time _timeSinceLastSpawn;
	sf::Vector2f _impulse;

	void shoot();
public:

	virtual ~Player();
	Player(const string& tag, const size_t id);
	Player(const string& tag, const size_t id,Configuration::Textures tex_id ,sf::Vector2f pos);
	Player(const string& tag, const size_t id,sf::Vector2f pos);

	std::shared_ptr<CRotation> ComponentRotation;

	std::shared_ptr<CCamera> CameraComponent;

	sf::Vector2f normalize(const sf::Vector2f& vector);

	virtual void update(sf::Time deltaTime) override;
	virtual void beginPlay() override;
	virtual void processEvent() override;
	virtual void setupInput() override;

	virtual void handleCollision(Actor& otherEntity) override;

	virtual void handleEndCollision(Actor& otherEntity) override;
};

