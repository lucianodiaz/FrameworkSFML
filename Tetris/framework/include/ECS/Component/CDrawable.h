#pragma once
#include <ECS/Component/Component.h>
#include <SFML/Graphics.hpp>
#include <Configuration/Configuration.h>

class CDrawable :
	public Component<CDrawable>
{
	sf::Texture _texture;
public:
	sf::Sprite sprite;

	CDrawable(Configuration::Textures tex_id) : _texture(Configuration::textures.get(tex_id))
	{
		sprite.setTexture(_texture);
		sprite.setOrigin(_texture.getSize().x / 2.f, _texture.getSize().y / 2.f);

	}

	CDrawable()
	{
		_texture = Configuration::textures.get(Configuration::Textures::Default);
		sprite.setTexture(_texture);
		sprite.setOrigin(_texture.getSize().x / 2.f, _texture.getSize().y / 2.f);
	}
};