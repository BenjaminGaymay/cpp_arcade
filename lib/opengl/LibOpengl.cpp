//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibOpengl
//

#include <iostream>
#include "LibOpengl.hpp"


using N_LibOpengl = arcade::LibOpengl;

N_LibOpengl::LibOpengl() :
	_width(sf::VideoMode::getDesktopMode().width),
	_height(sf::VideoMode::getDesktopMode().height),
	_window(sf::VideoMode(_width, _height), "Arcade", sf::Style::Close | sf::Style::Fullscreen),
	_font(),
	_text()
{
	_keyMatch[sf::Keyboard::Key::Up] = UP;
	_keyMatch[sf::Keyboard::Key::Down] = DOWN;
	_keyMatch[sf::Keyboard::Key::Left] = LEFT;
	_keyMatch[sf::Keyboard::Key::Right] = RIGHT;
	_keyMatch[sf::Keyboard::Key::Escape] = ESC;
	_keyMatch[sf::Keyboard::Key::Return] = ENTER;
	_keyMatch[sf::Keyboard::Key::P] = PAUSE;
	_keyMatch[sf::Keyboard::Key::R] = RESET;

	_text.setFont(_font);
	_sx = 30;
	_sy = _sx;
}

N_LibOpengl::~LibOpengl()
{}

void N_LibOpengl::drawText(const std::string &text, const int &x, const int &y, const Color &color)
{
	_text.setString(text);
	_text.setFillColor(_colorsMatch[color]);
	_text.setPosition(sf::Vector2f(x*_sx, y*_sy));
	_window.draw(_text);
}

bool N_LibOpengl::isOpen()
{
	return _window.isOpen();
}

void N_LibOpengl::openWindow()
{
	_window.setFramerateLimit(60);
	if (_font.loadFromFile("./ressources/Lato.ttf") == false)
		throw std::runtime_error("Error: openGl: can't load font.");
}

void N_LibOpengl::drawCube(float x, float y, const float size, const std::vector<int> &rgb)
{
	x = _mapWidth / 2 - x - size;
	y = _mapHeight / 2 - y - size;

	glTranslatef(-x, -y, size + 0.1);
	glBegin(GL_QUADS);

	glColor3ub(rgb[0], rgb[1], rgb[2]);

	// FRONT
	glVertex3f(-size,-size,size);
	glVertex3f(size,-size,size);
	glVertex3f(size,size,size);
	glVertex3f(-size,size,size);

	// BACK
	glVertex3f(-size,-size,-size);
	glVertex3f(-size,size,-size);
	glVertex3f(size,size,-size);
	glVertex3f(size,-size,-size);

	// LEFT
	glVertex3f(-size,-size,size);
	glVertex3f(-size,size,size);
	glVertex3f(-size,size,-size);
	glVertex3f(-size,-size,-size);

	// RIGHT
	glVertex3f(size,-size,-size);
	glVertex3f(size,size,-size);
	glVertex3f(size,size,size);
	glVertex3f(size,-size,size);

	// TOP
	glVertex3f(-size,size,size);
	glVertex3f(size,size,size);
	glVertex3f(size,size,-size);
	glVertex3f(-size,size,-size);

	// BOTTON
	glVertex3f(-size,-size,size);
	glVertex3f(-size,-size,-size);
	glVertex3f(size,-size,-size);
	glVertex3f(size,-size,size);

    	glEnd();
	glTranslatef(x, y, -(size + 0.1));
}

void N_LibOpengl::drawSquare(const int &x, const int &y, const Color &color)
{
	std::vector<int> rgb = getColor(color);

	if (color != BG_BLACK)
		drawCube(x, y, 0.5, getColor(color));
}

void N_LibOpengl::closeWindow()
{
	_window.close();
}

void N_LibOpengl::clearWindow()
{
	_window.clear(sf::Color::Black);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
}

void N_LibOpengl::refreshWindow()
{
	_window.display();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70,(double)getWidth()/getHeight(),1,1000);
	glEnable(GL_DEPTH_TEST);
	gluLookAt(0, _mapHeight / 4, _mapHeight, 0, 0, 0, 0, 0, 1);
	glRotatef(90, 0, 0, 1);
	glRotatef(-20, 0, 1, 0);
	glFlush();
}

int N_LibOpengl::getWidth()
{
	return _width / _sx;
}

int N_LibOpengl::getHeight()
{
	return _height / _sy;
}



std::vector<int> N_LibOpengl::getColor(const Color &c)
{
	switch (c) {
		case arcade::BG_RED:
			return {255, 0, 0};
		case arcade::BG_BLUE:
			return {0, 0, 255};
		case arcade::BG_GREEN:
			return {0, 255, 0};
		case arcade::BG_WHITE:
			return {255, 255, 255};
		case arcade::BG_CYAN:
			return {0, 255, 255};
		case arcade::BG_MAGENTA:
			return {255, 0, 255};
		case arcade::BG_YELLOW:
			return {255, 255, 0};
		default:
			return {0, 0, 0};
	}
}


arcade::Color N_LibOpengl::setColor(char c)
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
			return arcade::BG_BLUE;
		case 'o':
			return arcade::BG_RED;
		case '.':
			return arcade::BG_WHITE;
		case '1':
			return arcade::BG_BLUE;
		case '2':
			return arcade::BG_BLUE;
		case '3':
			return arcade::BG_BLUE;
		case '4':
			return arcade::BG_BLUE;
		case '5':
			return arcade::BG_CYAN;
		case '6':
			return arcade::BG_CYAN;
		case '7':
			return arcade::BG_CYAN;
		case '8':
			return arcade::BG_CYAN;
		default:
			return arcade::BG_BLACK;
	}
}

void N_LibOpengl::drawArena()
{
	glBegin(GL_QUADS);

	glColor3ub(50,50,50);
	glVertex3d((_mapHeight + 2) / 2, -(_mapWidth + 2) / 2, 0);
	glVertex3d((_mapHeight + 2) / 2, (_mapWidth + 2) / 2, 0);
	glVertex3d(-(_mapHeight + 2) / 2, (_mapWidth + 2) / 2, 0);
	glVertex3d(-(_mapHeight + 2) / 2, -(_mapWidth + 2) / 2, 0);

    	glEnd();
}

void N_LibOpengl::drawMap(const std::vector<std::string> &map)
{
	Color color;

	_mapWidth = 0;
	_mapHeight = map.size();
	for (auto &line : map) {
		if (_mapWidth < line.size())
			_mapWidth = line.size();
	}

	for (unsigned i = 0 ; i < map.size() ; i++) {
		for (unsigned j = 0 ; j < map[i].size() ; j++) {
			color = setColor(map[i][j]);
			drawSquare(i, j, color);
		}
	}
}

arcade::Key N_LibOpengl::getKey()
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
	return std::make_unique<arcade::LibOpengl>();
}