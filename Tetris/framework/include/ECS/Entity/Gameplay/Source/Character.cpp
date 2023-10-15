#include <ECS/Entity/Gameplay/include/Character.h>

Character::Character(const string& tag, const size_t id) : Pawn(tag, id)
{
}

Character::Character(const string& tag, const size_t id, Configuration::Textures tex_id) : Pawn(tag,id,tex_id)
{
}

Character::Character(const string& tag, const size_t id, sf::Vector2f pos) : Pawn(tag, id, pos)
{
}

Character::Character(const string& tag, const size_t id, Configuration::Textures tex_id,sf::Vector2f pos) : Pawn(tag,id,tex_id,pos)
{
}

void Character::update(sf::Time deltaTime)
{
	Pawn::update(deltaTime);
}

void Character::beginPlay()
{
	Pawn::beginPlay();
}

void Character::processEvent()
{
	Pawn::processEvent();
}

void Character::setupInput()
{
	Pawn::setupInput();
}

void Character::handleCollision(Entity<Actor>& otherEntity)
{
	Pawn::handleCollision(otherEntity);
}

void Character::handleEndCollision(Entity<Actor>& otherEntity)
{
	Pawn::handleEndCollision(otherEntity);
}
