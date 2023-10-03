#include "Window/Window.h"

Window::Window(int width, int height, string tittle):
	_width(width),_height(height),_tittle(tittle),
	_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(_width,_height),_tittle,sf::Style::Titlebar | sf::Style::Close))
{
}

Window::~Window()
{
}

bool Window::pollEvent(sf::Event& evt)
{
	return _window->pollEvent(evt);
}

void Window::clear()
{
	_window->clear();
}

void Window::draw(sf::Drawable& target, const sf::RenderStates& states)
{
	_window->draw(target, states);
}

void Window::display()
{
	_window->display();
}

void Window::close()
{
	_window->close();
}
