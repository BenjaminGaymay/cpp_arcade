//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibSfml
//

#include <iostream>
#include "LibSfml.hpp"


using N_LibSfml = arcade::LibSfml;

N_LibSfml::LibSfml() :
	_width(sf::VideoMode::getDesktopMode().width),
	_height(sf::VideoMode::getDesktopMode().height),
	_window(sf::VideoMode(_width, _height), "Arcade", sf::Style::Close | sf::Style::Fullscreen),
	_font(),
	_text()
{
	_colorsMatch[RED] = sf::Color::Red;
	_colorsMatch[BG_RED] = sf::Color::Red;
	_colorsMatch[BLUE] = sf::Color::Blue;
	_colorsMatch[BG_BLUE] = sf::Color::Blue;
	_colorsMatch[GREEN] = sf::Color::Green;
	_colorsMatch[BG_GREEN] = sf::Color::Green;

	_keyMatch[sf::Keyboard::Key::Up] = UP;
	_keyMatch[sf::Keyboard::Key::Down] = DOWN;
	_keyMatch[sf::Keyboard::Key::Left] = LEFT;
	_keyMatch[sf::Keyboard::Key::Right] = RIGHT;
	_keyMatch[sf::Keyboard::Key::Return] = ENTER;
	_keyMatch[sf::Keyboard::Key::Escape] = ESC;
}

N_LibSfml::~LibSfml()
{
}

void N_LibSfml::drawText(const std::string &text, const int &x, const int &y, const Color &color)
{
	_text.setString(text);
	_text.setFillColor(_colorsMatch[color]);
	_text.setPosition(x, y);
	_window.draw(_text);
}

void N_LibSfml::openWindow()
{
	// _window.create(sf::VideoMode(_width, _height), "Arcade", sf::Style::Close | sf::Style::Fullscreen);
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(60);
	if (_font.loadFromFile("./ressources/Lato.ttf") == false)
		throw std::runtime_error("Error: sfml: can't load font.");
}

void N_LibSfml::drawSquare(const int &x, const int &y, const Color &color)
{
	sf::RectangleShape rect;
	rect.setFillColor(_colorsMatch[color]);
	rect.setSize(sf::Vector2f(200,200));
	rect.setPosition(x, y);
	_window.draw(rect);
}

void N_LibSfml::closeWindow()
{
	_window.close();
}

void N_LibSfml::clearWindow()
{
	_window.clear(sf::Color::Black);
}

void N_LibSfml::refreshWindow()
{
	_window.display();
}

arcade::IGraphics::Key N_LibSfml::getKey()
{
	for (auto &c : _keyMatch)
		if (sf::Keyboard::isKeyPressed(c.first))
			return c.second;
	return NONE;
}

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibSfml>();
}