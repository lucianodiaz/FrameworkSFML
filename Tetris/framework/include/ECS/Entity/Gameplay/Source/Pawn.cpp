#include <ECS/Entity/Gameplay/include/Pawn.h>



Pawn::Pawn(const string& tag, const size_t id) : Actor(tag, id),
ActionTarget(Configuration::playerInputs)
{
	ComponentDrawable = addComponent<CDrawable>();
}

Pawn::Pawn(const string& tag, const size_t id, Configuration::Textures tex_id) : Actor(tag, id),
ActionTarget(Configuration::playerInputs)
{
	ComponentDrawable = addComponent<CDrawable>(tex_id);
}

Pawn::Pawn(const string& tag, const size_t id, sf::Vector2f pos) :Actor(tag, id, pos),
ActionTarget(Configuration::playerInputs)
{
	ComponentDrawable = addComponent<CDrawable>();
}

Pawn::Pawn(const string& tag, const size_t id, Configuration::Textures tex_id, sf::Vector2f pos):Actor(tag,id,pos),
ActionTarget(Configuration::playerInputs)
{
	ComponentDrawable = addComponent<CDrawable>(tex_id);
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
}

void Pawn::setupInput()
{
}
