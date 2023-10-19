#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Input/ActionMap.h>
#include <ResourceManager.h>

class Configuration
{
public:
	Configuration() = delete;
	Configuration(const Configuration&) = delete;
	Configuration& operator=(const Configuration&) = delete;

	enum PlayerInputs : int
	{
		Up,
		Down,
		Right,
		Left,
		LeftClick
	};
	static ActionMap<int>playerInputs;

	enum Textures :int
	{
		Default,
		Barrel,
		Human,
		Ship
	};

	static ResourceManager<sf::Texture> textures;


	static void initialize();

private:
	static void initTextures();
	static void initMusic();
	static void initFonts();
	static void initGuiInputs();
	static void initInputs();
	static void initShareds();
};


