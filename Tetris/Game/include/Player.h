#pragma once
#include <memory>
#include <ECS/Entity/Gameplay/Actor.h>
#include <ECS/Component/CDrawable.h>
#include <Input/ActionTarget.h>

class Player :
	public Actor, public ActionTarget<int>
{
public:

	Player(const string& tag, const size_t id);

	virtual void update(sf::Time deltaTime);
	virtual void beginPlay();
	void processEvent();
};

