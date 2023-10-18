#include <ECS/Entity/Gameplay/include/Pawn.h>



Pawn::Pawn(const string& tag, const size_t id) : Actor(tag, id),
ActionTarget(Configuration::playerInputs)
{
	ComponentDrawable = addComponent<CDrawable>();
	beginPlay();
}

Pawn::Pawn(const string& tag, const size_t id, Configuration::Textures tex_id) : Actor(tag, id),
ActionTarget(Configuration::playerInputs)
{
	ComponentDrawable = addComponent<CDrawable>(tex_id);
	beginPlay();
}

Pawn::Pawn(const string& tag, const size_t id, sf::Vector2f pos) :Actor(tag, id, pos),
ActionTarget(Configuration::playerInputs)
{
	ComponentDrawable = addComponent<CDrawable>();
	beginPlay();
}

Pawn::Pawn(const string& tag, const size_t id, Configuration::Textures tex_id, sf::Vector2f pos):Actor(tag,id,pos),
ActionTarget(Configuration::playerInputs)
{
	ComponentDrawable = addComponent<CDrawable>(tex_id);
	beginPlay();
}

void Pawn::processEvent()
{
	ActionTarget::processEvents();
}

void Pawn::update(sf::Time deltaTime)
{
	Actor::update(deltaTime);
}

void Pawn::beginPlay()
{
	Actor::beginPlay();
	CollisionComponent = addComponent<CCollision>(ComponentDrawable->sprite.getGlobalBounds());
}

void Pawn::setupInput()
{
}

void Pawn::handleCollision(Entity<Actor>& otherEntity)
{
	Actor::handleCollision(otherEntity);
}

void Pawn::handleEndCollision(Entity<Actor>& otherEntity)
{
	Actor::handleEndCollision(otherEntity);
}
