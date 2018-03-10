//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibSfml
//

#include <iostream>
#include "LibSfml.hpp"


using N_LibSfml = arcade::LibSfml;

N_LibSfml::LibSfml()
{
}

N_LibSfml::~LibSfml()
{
}

void N_LibSfml::drawText(const std::string &text, const int &x, const int &y, const Color &color)
{
	_text.setString(text);
	_text.setPosition(x, y);
	_window.draw(_text);
}

void N_LibSfml::openWindow()
{
	_width = sf::VideoMode::getDesktopMode().width;
	_height = sf::VideoMode::getDesktopMode().height;
	_window.create(sf::VideoMode(_width, _height), "Arcade", sf::Style::Fullscreen);
	if (_font.loadFromFile("./ressources/Lato.ttf") == false)
		throw std::runtime_error("Error: sfml: can't load font.");
}

void N_LibSfml::drawSquare(const int &x, const int &y, const Color &color)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(20,20));
	rect.setPosition(x, y);
}

void N_LibSfml::closeWindow()
{
	_window.close();
}

void N_LibSfml::clearWindow()
{
	_window.clear();
}

void N_LibSfml::refreshWindow()
{
	_window.display();
}

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibSfml>();
}