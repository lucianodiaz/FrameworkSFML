#pragma 
#include <iostream>
#include <SFML/Graphics.hpp>

using std::string;

class Window
{
private:
	int _width;
	int _height;
	string _tittle;
	std::unique_ptr<sf::RenderWindow> _window;
public:
	Window(int width, int height, string tittle);
	virtual ~Window();

	const sf::Vector2u& getWindowCenterPos()const { return sf::Vector2u(_window->getSize().x / 2, _window->getSize().y / 2); };
	sf::RenderWindow& getRenderWindow() { return *_window; };
	bool isOpen() const { return _window->isOpen(); };
	bool pollEvent(sf::Event& evt);

	void clear();
	void draw(sf::Drawable& target, const sf::RenderStates& states = sf::RenderStates::Default);
	void display();
	void close();

};

