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
	_colorsMatch[BLUE] = sf::Color::Blue;
	_colorsMatch[GREEN] = sf::Color::Green;
	_colorsMatch[BG_RED] = sf::Color::Red;
	_colorsMatch[BG_BLUE] = sf::Color::Blue;
	_colorsMatch[BG_GREEN] = sf::Color::Green;
	_colorsMatch[BG_WHITE] = sf::Color::White;
	_colorsMatch[WHITE] = sf::Color::White;
	_colorsMatch[BG_BLACK] = sf::Color::Black;

	_keyMatch[sf::Keyboard::Key::Z] = UP;
	_keyMatch[sf::Keyboard::Key::S] = DOWN;
	_keyMatch[sf::Keyboard::Key::Q] = LEFT;
	_keyMatch[sf::Keyboard::Key::D] = RIGHT;
	_keyMatch[sf::Keyboard::Key::A] = ESC;
	_keyMatch[sf::Keyboard::Key::E] = ENTER;
	_keyMatch[sf::Keyboard::Key::P] = PAUSE;
	_keyMatch[sf::Keyboard::Key::R] = RESET;

	_text.setFont(_font);
	_sx = 20;
	_sy = _sx;

	loadTexture("./ressources/images/grass.png"); // 0
	loadTexture("./ressources/images/brick.png"); // 1
	loadTexture("./ressources/images/apple.png"); // 2
	// _textureMatch[GREEN] = _texture[0];

	// _textureMatch[BG_GREEN] = _texture[0];
	_textureMatch[BG_BLACK] = _texture[0];
	_textureMatch[BG_WHITE] = _texture[1];
	_textureMatch[BG_RED] = _texture[2];

	_textureMatch[GRASS] = _texture[0];
	_textureMatch[BRICK] = _texture[1];
	_textureMatch[APPLE] = _texture[2];
}

N_LibSfml::~LibSfml()
{}

void N_LibSfml::loadTexture(const std::string &path)
{
	sf::Texture texture;

	if (texture.loadFromFile(path) == false)
		throw std::runtime_error("Error: ressources: Can't load sprites");
	_texture.push_back(texture);
}

void N_LibSfml::drawText(const std::string &text, const int &x, const int &y, const Color &color)
{
	_text.setString(text);
	_text.setFillColor(_colorsMatch[color]);
	_text.setPosition(sf::Vector2f(x*_sx, y*_sy));
	_window.draw(_text);
}

bool N_LibSfml::isOpen()
{
	return _window.isOpen();
}

void N_LibSfml::openWindow()
{
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(60);
	if (_font.loadFromFile("./ressources/Lato.ttf") == false)
		throw std::runtime_error("Error: sfml: can't load font.");
}

void N_LibSfml::drawSquare(const int &x, const int &y, const Color &color)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(_sx,_sy));
	rect.setPosition(sf::Vector2f(x*_sx, y*_sy));

	if (_textureMatch.find(color) != _textureMatch.end())
		rect.setTexture(&_textureMatch[color]);
	else
		rect.setFillColor(_colorsMatch[color]);

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

int N_LibSfml::getWidth()
{
	return _width / _sx;
}

int N_LibSfml::getHeight()
{
	return _height / _sy;
}

arcade::Color N_LibSfml::setColor(char c)
{
	switch (c) {
		case 'W':
			return arcade::BG_WHITE;
		case 'G':
			return arcade::BG_GREEN;
		case 'R':
			return arcade::BG_RED;
		default:
			return arcade::BG_BLACK;
	}
}

void N_LibSfml::drawMap(const std::vector<std::string> &map)
{
	arcade::Color color;

	for (unsigned i = 0 ; i < map.size() ; i++) {
		for (unsigned j = 0 ; j < map[i].size() ; j++) {
			color = setColor(map[i][j]);
			drawSquare(getWidth() / 2 - (map[i].size() / 2 - 1) + j, getHeight() / 2 - (map.size() / 2) + i, color);
		}
	}
}

arcade::Key N_LibSfml::getKey()
{
	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed)
			return _keyMatch[event.key.code];
	}
	return NONE;
	_window.pollEvent(event);
	if (event.type == sf::Event::KeyPressed)
		return _keyMatch[event.key.code];
	return NONE;
}

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibSfml>();
}