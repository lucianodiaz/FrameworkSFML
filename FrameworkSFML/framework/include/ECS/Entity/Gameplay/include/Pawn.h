#pragma once
#include "Actor.h"
#include "Input/ActionTarget.h"
#include "Configuration/Configuration.h"
#include <ECS/Component/CDrawable.h>
#include <ECS/Component/CCollision.h>

class Pawn : public Actor,
	public ActionTarget<int>
{
public:

	virtual ~Pawn(){};
	Pawn(const string& tag, const size_t id);
	Pawn(const string& tag, const size_t id, Configuration::Textures tex_id);
	Pawn(const string& tag, const size_t id, sf::Vector2f pos);
	Pawn(const string& tag, const size_t id, Configuration::Textures tex_id,sf::Vector2f pos);

	std::shared_ptr<CDrawable> ComponentDrawable;
	std::shared_ptr<CCollision> CollisionComponent;

	virtual void processEvent();
	virtual void update(sf::Time deltaTime) override;
	virtual void beginPlay() override;
	virtual void setupInput();

	virtual void handleCollision(Entity<Actor>& otherEntity) override;
	virtual void handleEndCollision(Entity<Actor>& otherEntity) override;
};