#include "Player.h"
#include "World.h"
#include <Shoot/Shoot.h>


Player::~Player()
{
}

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
	ComponentRotation = addComponent<CRotation>(0);  // Direcci�n inicial: derecha, rotaci�n inicial: 0 grados
	_isMoving = false;

	CameraComponent = addComponent<CCamera>(sf::Vector2f(ComponentTransform->position.x / 2, ComponentTransform->position.y / 2), sf::Vector2f(getWorld()->getWindow()->getRenderWindow().getSize()));
	CameraComponent->LagFactor = 0.1;

	getWorld()->setCamera(CameraComponent->Camera);
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
		float angleInRadians = (ComponentRotation->getRotation()) * 3.14159265 / 180; // Convierte el �ngulo a radianes

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
		ComponentRotation->addRotation -= 1.5;
		});

	bind(Configuration::PlayerInputs::Right, [this](const sf::Event&) {
		// Rotar a la derecha (sentido horario)
		ComponentRotation->addRotation += 1.5;
		});

	bind(Configuration::PlayerInputs::LeftClick, [this](const sf::Event&)
		{
			shoot();
		});
}
void Player::shoot()
{
	if (_timeSinceLastSpawn > sf::seconds(0.2))
	{
		auto newPos = sf::Vector2f( ComponentTransform->position.x, ComponentTransform->position.y);
		float angleInRadians = (ComponentRotation->getRotation()) * 3.14159265 / 180; // Convierte el �ngulo a radianes
		sf::Vector2f direction(cos(angleInRadians), sin(angleInRadians));

		auto offset = 70.0f * direction;


		auto shoot = getWorld()->spawnEntity<Shoot>("shoot", Configuration::Textures::ShootPlayer,newPos+ offset, ComponentRotation->getRotation());
		auto p = shared_from_this();
		shoot->SetOwner(p);

		float velocity = sqrt((_impulse.x * _impulse.x) + (_impulse.y * _impulse.y));
		shoot->getComponentProjectile().speed += velocity;


		//shoot->attachTo(p, offset);
		_timeSinceLastSpawn = sf::Time::Zero;
	}
	
}

void Player::handleCollision(Actor& otherEntity)
{
	Character::handleCollision(otherEntity);
}

void Player::handleEndCollision(Actor& otherEntity)
{
	Character::handleEndCollision(otherEntity);
}
