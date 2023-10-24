#include "Player.h"
#include "World.h"
#include <Shoot/Shoot.h>

Player::Player(const string& tag, const size_t id) : Character(tag, id)
{
	beginPlay();
}

Player::Player(const string& tag, const size_t id, Configuration::Textures tex_id, sf::Vector2f pos) : Character(tag, id, tex_id, pos)
{
	beginPlay();
}

Player::Player(const string& tag, const size_t id, sf::Vector2f pos) : Character(tag, id, pos)
{
	beginPlay();
}

void Player::beginPlay()
{
	Character::beginPlay();
	_impulse = sf::Vector2f(0, 0);
	ComponentRotation = addComponent<CRotation>(0);  // Dirección inicial: derecha, rotación inicial: 0 grados
	_isMoving = false;
	setupInput();
}

sf::Vector2f Player::normalize(const sf::Vector2f& vector)
{
	float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	if (length != 0)
		return sf::Vector2f(vector.x / length, vector.y / length);
	else
		return vector;
}

void Player::update(sf::Time deltaTime) {
	float seconds = deltaTime.asSeconds();
	_timeSinceLastSpawn += deltaTime;

	if (_isMoving)
	{
		float angleInRadians = (ComponentRotation->rotation) * 3.14159265 / 180; // Convierte el ángulo a radianes

		_impulse += sf::Vector2f(cos(angleInRadians), sin(angleInRadians)) * 100.0f * seconds;
	}

 	ComponentTransform->offset = seconds * _impulse;
}



void Player::processEvent()
{
	ComponentRotation->addRotation = 0;
	_isMoving = false;
	ActionTarget::processEvents();
}

void Player::setupInput()
{
	Character::setupInput();


	bind(Configuration::PlayerInputs::Up, [this](const sf::Event&)
		{
			_isMoving = true;

		});

	bind(Configuration::PlayerInputs::Down, [this](const sf::Event&)
		{
			
		});

	bind(Configuration::PlayerInputs::Left, [this](const sf::Event&) {
		// Rotar a la izquierda (sentido antihorario)
		ComponentRotation->addRotation -= 1;
		});

	bind(Configuration::PlayerInputs::Right, [this](const sf::Event&) {
		// Rotar a la derecha (sentido horario)
		ComponentRotation->addRotation += 1;
		});

	bind(Configuration::PlayerInputs::LeftClick, [this](const sf::Event&)
		{
			shoot();
		});
}
void Player::shoot()
{
	if (_timeSinceLastSpawn > sf::seconds(0.3))
	{
		auto newPos = sf::Vector2f( ComponentTransform->position.x, ComponentTransform->position.y);
		
		float angleInRadians = (ComponentRotation->rotation) * 3.14159265 / 180; // Convierte el ángulo a radianes
		sf::Vector2f direction(cos(angleInRadians), sin(angleInRadians));

		auto offset = 70.0f * direction;


		auto shoot = getWorld()->spawnEntity<Shoot>("Shoot", Configuration::Textures::Barrel,newPos+ offset, ComponentRotation->rotation);
		auto p = shared_from_this();


		//shoot->attachTo(p, offset);
		_timeSinceLastSpawn = sf::Time::Zero;
	}
	
}

void Player::handleCollision(Entity<Actor>& otherEntity)
{
	Character::handleCollision(otherEntity);
}

void Player::handleEndCollision(Entity<Actor>& otherEntity)
{
	Character::handleEndCollision(otherEntity);
}
