#include "Configuration/Configuration.h"


ResourceManager<sf::Texture, int>Configuration::textures;

ActionMap<int>Configuration::playerInputs;

void Configuration::initialize()
{
	initFonts();
	initMusic();
	initTextures();
	initInputs();
	initGuiInputs();
	initShareds();
}

void Configuration::initTextures()
{
	textures.load(Textures::Barrel, "assets/Sprites/barrel.png");
	textures.load(Textures::Default, "assets/Sprites/default.png");
	textures.load(Textures::Human, "assets/Sprites/human.png");
}

void Configuration::initMusic()
{
}

void Configuration::initFonts()
{
}

void Configuration::initGuiInputs()
{
}

void Configuration::initInputs()
{
	//playerInputs.map(PlayerInputs::Up, Action(sf::Keyboard::Up));
	playerInputs.map(PlayerInputs::Up, Action(sf::Keyboard::W));

	//playerInputs.map(PlayerInputs::Down, Action(sf::Keyboard::Down));
	playerInputs.map(PlayerInputs::Down, Action(sf::Keyboard::S));

	//playerInputs.map(PlayerInputs::Left, Action(sf::Keyboard::Left));
	playerInputs.map(PlayerInputs::Left, Action(sf::Keyboard::A));

	//playerInputs.map(PlayerInputs::Right, Action(sf::Keyboard::Right));
	playerInputs.map(PlayerInputs::Right, Action(sf::Keyboard::D));
}

void Configuration::initShareds()
{
}
