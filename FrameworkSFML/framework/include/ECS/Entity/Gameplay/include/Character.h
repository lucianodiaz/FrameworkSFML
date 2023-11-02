#pragma once
#include "Pawn.h"

class Character : public Pawn
{
public:
	virtual ~Character() {};
	Character(const string& tag, const size_t id);
	Character(const string& tag, const size_t id,Configuration::Textures tex_id);
	Character(const string& tag, const size_t id, sf::Vector2f pos);
	Character(const string& tag, const size_t id, Configuration::Textures tex_id,sf::Vector2f pos);

	virtual void update(sf::Time deltaTime) override;
	virtual void beginPlay() override;
	void processEvent() override;
	void setupInput() override;
	virtual void handleCollision(Actor& otherEntity) override;
	virtual void handleEndCollision(Actor& otherEntity) override;
};