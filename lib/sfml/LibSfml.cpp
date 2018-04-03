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
	_colorsMatch[WHITE] = sf::Color::White;
	_colorsMatch[BLACK] = sf::Color::Black;
	_colorsMatch[CYAN] = sf::Color::Cyan;
	_colorsMatch[MAGENTA] = sf::Color::Magenta;
	_colorsMatch[YELLOW] = sf::Color::Yellow;
	_colorsMatch[BG_RED] = sf::Color::Red;
	_colorsMatch[BG_BLUE] = sf::Color::Blue;
	_colorsMatch[BG_GREEN] = sf::Color::Green;
	_colorsMatch[BG_WHITE] = sf::Color::White;
	_colorsMatch[BG_BLACK] = sf::Color::Black;
	_colorsMatch[BG_CYAN] = sf::Color::Cyan;
	_colorsMatch[BG_MAGENTA] = sf::Color::Magenta;
	_colorsMatch[BG_YELLOW] = sf::Color::Yellow;

	_keyMatch[sf::Keyboard::Key::Up] = UP;
	_keyMatch[sf::Keyboard::Key::Down] = DOWN;
	_keyMatch[sf::Keyboard::Key::Left] = LEFT;
	_keyMatch[sf::Keyboard::Key::Right] = RIGHT;
	_keyMatch[sf::Keyboard::Key::Escape] = ESC;
	_keyMatch[sf::Keyboard::Key::Return] = ENTER;
	_keyMatch[sf::Keyboard::Key::P] = PAUSE;
	_keyMatch[sf::Keyboard::Key::R] = RESET;
	_keyMatch[sf::Keyboard::Key::B] = PREVIOUS;
	_keyMatch[sf::Keyboard::Key::N] = NEXT;
	_keyMatch[sf::Keyboard::Key::S] = SHOOT;

	_text.setFont(_font);
	_sx = 30;
	_sy = _sx;

	loadTexture("./ressources/images/grass.png"); // 0
	loadTexture("./ressources/images/brick.png"); // 1
	loadTexture("./ressources/images/apple.png"); // 2
	loadTexture("./ressources/images/brick_head.png"); // 3
	loadTexture("./ressources/images/gum.png"); // 4
	loadTexture("./ressources/images/wood.png"); // 5
	loadTexture("./ressources/images/pacman_right.png"); // 6
	loadTexture("./ressources/images/pacman_left.png"); // 7
	loadTexture("./ressources/images/pacman_top.png"); // 8
	loadTexture("./ressources/images/pacman_down.png"); // 9
	loadTexture("./ressources/images/body_right.png"); // 10
	loadTexture("./ressources/images/body_left.png"); // 11
	loadTexture("./ressources/images/body_top.png"); // 12
	loadTexture("./ressources/images/body_down.png"); // 13
	loadTexture("./ressources/images/superpacman_right.png"); // 14
	loadTexture("./ressources/images/superpacman_left.png"); // 15
	loadTexture("./ressources/images/superpacman_top.png"); // 16
	loadTexture("./ressources/images/superpacman_down.png"); // 17
	loadTexture("./ressources/images/biggum.png"); // 18
	// _textureMatch[GREEN] = _texture[0];

	_textureMatch[GREEN] = _texture[0];

	_textureMatch[BG_GREEN] = _texture[0];
	_textureMatch[BG_BLACK] = _texture[0];
	_textureMatch[BG_WHITE] = _texture[1];
	_textureMatch[BG_RED] = _texture[2];

	_textureMatch[GRASS] = _texture[0];
	_textureMatch[BRICK] = _texture[1];
	_textureMatch[APPLE] = _texture[2];
	_textureMatch[BRICK_HEAD] = _texture[3];
	_textureMatch[GUM] = _texture[4];
	_textureMatch[WOOD] = _texture[5];

	_textureMatch[HEAD_RIGHT] = _texture[6];
	_textureMatch[HEAD_LEFT] = _texture[7];
	_textureMatch[HEAD_TOP] = _texture[8];
	_textureMatch[HEAD_DOWN] = _texture[9];

	_textureMatch[BODY_RIGHT] = _texture[10];
	_textureMatch[BODY_LEFT] = _texture[11];
	_textureMatch[BODY_TOP] = _texture[12];
	_textureMatch[BODY_DOWN] = _texture[13];

	_textureMatch[SHEAD_RIGHT] = _texture[14];
	_textureMatch[SHEAD_LEFT] = _texture[15];
	_textureMatch[SHEAD_TOP] = _texture[16];
	_textureMatch[SHEAD_DOWN] = _texture[17];

	_textureMatch[SUPERGUM] = _texture[18];
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
	_window.setFramerateLimit(60);
	if (_font.loadFromFile("./ressources/Lato.ttf") == false)
		throw std::runtime_error("Error: sfml: can't load font.");
}

void N_LibSfml::drawSquare(const int &x, const int &y, const Color &color)
{
	sf::RectangleShape rect;
	sf::Sprite sprite;

	rect.setSize(sf::Vector2f(_sx,_sy));
	rect.setPosition(sf::Vector2f(x*_sx, y*_sy));
	sprite.setPosition(sf::Vector2f(x*_sx, y*_sy));
	if (_textureMatch.find(color) != _textureMatch.end()) {
		sprite.setTexture(_textureMatch[color]);
		_window.draw(sprite);
	}
	else {
		rect.setFillColor(_colorsMatch[color]);
		_window.draw(rect);
	}
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
	return _width;
}

int N_LibSfml::getHeight()
{
	return _height;
}

int N_LibSfml::getScaleWidth()
{
	return _width / _sx;
}

int N_LibSfml::getScaleHeight()
{
	return _height / _sy;
}

arcade::Color N_LibSfml::setColor(char c)
{
	switch (c) {
		case 'R':
			return arcade::BG_RED;
		case 'B':
			return arcade::BG_BLUE;
		case 'G':
			return arcade::BG_GREEN;
		case 'W':
			return arcade::BG_WHITE;
		case 'C':
			return arcade::BG_CYAN;
		case 'M':
			return arcade::BG_MAGENTA;
		case 'Y':
			return arcade::BG_YELLOW;
		case '#':
			return arcade::BRICK;
		case 'o':
			return arcade::APPLE;
		case '.':
			return arcade::GUM;
		case '1':
			return arcade::HEAD_RIGHT;
		case '2':
			return arcade::HEAD_LEFT;
		case '3':
			return arcade::HEAD_TOP;
		case '4':
			return arcade::HEAD_DOWN;
		case 'a':
			return arcade::SHEAD_RIGHT;
		case 'b':
			return arcade::SHEAD_LEFT;
		case 'c':
			return arcade::SHEAD_TOP;
		case 'd':
			return arcade::SHEAD_DOWN;
		case '5':
			return arcade::BODY_RIGHT;
		case '6':
			return arcade::BODY_LEFT;
		case '7':
			return arcade::BODY_TOP;
		case '8':
			return arcade::BODY_DOWN;
		case 's':
			return arcade::SUPERGUM;
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
			if (i + 1 < map.size() and color == arcade::BRICK and setColor(map[i + 1][j]) == arcade::BRICK)
				color = arcade::BRICK_HEAD;
			drawSquare(getScaleWidth() / 2 - (map[i].size() / 2 - 1) + j, getScaleHeight() / 2 - (map.size() / 2) + i, color);
		}
	}
}

arcade::Key N_LibSfml::getKey()
{
	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed
			and _keyMatch.find(event.key.code) != _keyMatch.end())
			return _keyMatch[event.key.code];
	}
	return NONE;
}

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibSfml>();
}