#pragma once
#include <memory>
#include <ECS/Entity/Gameplay/Actor.h>
#include <ECS/Component/CTransform.h>
#include <ECS/Component/CShape.h>

class Player :
	public Actor
{
public:

	Player(const string& tag, const size_t id);

	virtual void update(sf::Time deltaTime);
	virtual void beginPlay();
	void processEvent();
	std::shared_ptr <CDrawable> cDrawable;
};

