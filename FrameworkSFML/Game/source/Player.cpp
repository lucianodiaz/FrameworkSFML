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
	ComponentRotation = addComponent<CRotation>();  // Dirección inicial: derecha, rotación inicial: 0 grados
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

	// Normalizar la dirección
	ComponentRotation->direction = normalize(ComponentRotation->direction);

	// Actualizar la posición de la nave según su dirección y velocidad
	if (_isMoving) {
		_impulse += ComponentRotation->direction * 100.0f * seconds;
	}

	// Actualizar la posición de la nave
	ComponentTransform->position += _impulse * seconds;

	// Calcular la rotación en grados
	float angle = std::atan2(ComponentRotation->direction.y, ComponentRotation->direction.x);
	angle = angle * 180.0f /3.14159;

	// Aplicar la rotación al sprite
	ComponentDrawable->sprite.setRotation(angle * 180.0f / 3.14159);
}



void Player::processEvent()
{
	/*setVelocity(0, 0);*/
	_isMoving = false;
	ActionTarget::processEvents();
	/*isPressed = false;*/
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
		ComponentRotation->direction = sf::Vector2f(
			-ComponentRotation->direction.y,
			ComponentRotation->direction.x
		);
		});

	bind(Configuration::PlayerInputs::Right, [this](const sf::Event&) {
		// Rotar a la derecha (sentido horario)
		ComponentRotation->direction = sf::Vector2f(
			ComponentRotation->direction.y,
			-ComponentRotation->direction.x
		);
		});

	bind(Configuration::PlayerInputs::LeftClick, [this](const sf::Event&)
		{
			//shoot();
		});
}
void Player::shoot()
{
	if (_timeSinceLastSpawn > sf::seconds(0.3))
	{

		//getWorld()->spawnEntity<Shoot>("Shoot", Configuration::Textures::Barrel,ComponentTransform->position, ComponentRotation->rotation);
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
