#include "Enemy/Meteors/Meteor.h"
#include "Math/Random.h"

Meteor::Meteor(const string& tag, const size_t id) : Actor(tag,id)
{
	ComponentDrawable = addComponent<CDrawable>();
	ComponentRotation = addComponent<CRotation>();
	beginPlay();
}

Meteor::Meteor(const string& tag, const size_t id, Configuration::Textures tex_id, sf::Vector2f pos) : Actor(tag, id, pos)
{
	ComponentDrawable = addComponent<CDrawable>(tex_id);
	ComponentRotation = addComponent<CRotation>();
	beginPlay();
}

Meteor::Meteor(const string& tag, const size_t id, sf::Vector2f pos) : Actor(tag, id, pos)
{
	ComponentDrawable = addComponent<CDrawable>();
	ComponentRotation = addComponent<CRotation>();
	beginPlay();
}

Meteor::~Meteor()
{
}

void Meteor::beginPlay()
{
	Actor::beginPlay();
	ComponentCollision = addComponent<CCollision>(ComponentDrawable->sprite.getGlobalBounds());
	
	rotationSpeed = randomlib::random(0.5f, 1.0f);

	ComponentRotation->rotation = randomlib::random(0, 360);

	float rotationInRadians = ComponentRotation->rotation * 3.14159 / 180.0;
	auto dirX = std::cos(rotationInRadians);
	auto dirY = std::sin(rotationInRadians);

	float length = sqrt(dirX * dirX + dirY * dirY);
	if (length != 0) {
		dirX /= length;
		dirY /= length;
	}
	sf::Vector2f direction = sf::Vector2f(dirX, dirY) ;

	ComponentTransform->setVelocity(direction * randomlib::random(1.0f, 10.0f));
	std::cout << "Rotation Speed: " << rotationSpeed << std::endl;
}


void Meteor::update(sf::Time deltaTime)
{
	ComponentRotation->addRotation = rotationSpeed;
}


void Meteor::handleCollision(Actor& otherEntity)
{
	if (otherEntity.tag() == "shoot"/* && otherEntity.GetOwner()->tag()=="ship"*/)
	{
		life--;
		std::cout << "life :" << life << std::endl;
		if (life <= 0)
		{
			destroy();
		}
	}
}

void Meteor::handleEndCollision(Actor& otherEntity)
{
}
