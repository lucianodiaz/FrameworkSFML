#pragma once
#include <memory>
#include <Input/ActionTarget.h>
#include <ECS/Entity/Gameplay/include/Character.h>
class Player : public Character
{
public:

	Player(const string& tag, const size_t id);
	Player(const string& tag, const size_t id,Configuration::Textures tex_id ,sf::Vector2f pos);
	Player(const string& tag, const size_t id,sf::Vector2f pos);

	virtual void update(sf::Time deltaTime) override;
	virtual void beginPlay() override;
	virtual void processEvent() override;
	virtual void setupInput() override;
};

