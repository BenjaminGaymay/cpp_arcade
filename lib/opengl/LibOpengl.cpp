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
	_keyMatch[sf::Keyboard::Key::B] = PREVIOUS_LIB;
	_keyMatch[sf::Keyboard::Key::N] = NEXT_LIB;
	_keyMatch[sf::Keyboard::Key::M] = NEXT_GAME;
	_keyMatch[sf::Keyboard::Key::L] = PREVIOUS_GAME;
	_keyMatch[sf::Keyboard::Key::S] = SHOOT;

	_mapHeight = 30;
	_mapWidth = 30;

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

void N_LibOpengl::drawCube(float x, float y, const GLfloat size, const std::vector<int> &rgb)
{
	glEnable(GL_DEPTH_TEST);
	x = _mapWidth / 2 - x - size;
	y = _mapHeight / 2 - y - size;

	glTranslatef(-x, -y, size + 0.1);

	glBegin(GL_QUADS);
	glColor3ub(rgb[0], rgb[1], rgb[2]);

	// BACK
	glVertex3f(size, -size, size);
	glVertex3f(size, size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, -size, size);

	// RIGHT
	glVertex3f(size, -size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(size, size, size);
	glVertex3f(size, -size, size);

	// LEFT
	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, size, -size);
	glVertex3f(-size, -size, -size);

	// TOP
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);

	// BOTTOM
	glVertex3f(size, -size, -size);
	glVertex3f(size, -size, size);
	glVertex3f(-size, -size, size);
	glVertex3f(-size, -size, -size);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
	_window.clear(sf::Color::Black);
}

void N_LibOpengl::refreshWindow()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glDepthFunc(GL_LESS);
	gluPerspective(70, static_cast<double>(getWidth()) / static_cast<double>(getHeight()), 1, 1000);
	gluLookAt(0, _mapHeight / 4, _mapWidth, 0, 0, 0, 0, 0, 1);
	glRotatef(90, 0, 0, 1);
	glRotatef(-20, 0, 1, 0);
	glFlush();
	_window.display();
	_window.resetGLStates();
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
		case 'o':
		case 'h':
			return arcade::BG_RED;
		case 'B':
		case 'g':
		case '#':
			return arcade::BG_BLUE;
		case 'G':
		case '5':
		case '6':
		case '7':
		case '8':
		case 'e':
			return arcade::BG_GREEN;
		case 'W':
		case '.':
			return arcade::BG_WHITE;
		case 'C':
		case 'i':
			return arcade::BG_CYAN;
		case 'M':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'f':
			return arcade::BG_MAGENTA;
		case 'Y':
		case '1':
		case '2':
		case '3':
		case '4':
		case 's':
			return arcade::BG_YELLOW;
		default:
			return arcade::BG_BLACK;
	}
}

void N_LibOpengl::drawMap(const std::vector<std::string> &map)
{
	Color color;
	unsigned lineSize;

	_mapWidth = 0;
	_mapHeight = map.size();
	for (auto &line : map) {
		if (_mapWidth < line.size())
			_mapWidth = line.size();
	}

	for (unsigned i = 0 ; i < map.size() ; i++) {
		lineSize = map[i].size();
		for (unsigned j = map[i].size() - 1 ; j >= (lineSize - 1) / 2 ; j--) {
			color = setColor(map[i][j]);
			drawSquare(i, j, color);
		}
		for (unsigned j = 0 ; j < (lineSize - 1) / 2 ; j++) {
			color = setColor(map[i][j]);
			drawSquare(i, j, color);
		}
	}
}

arcade::Key N_LibOpengl::getKey()
{
	sf::Event event;

	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			_key = event.key.code;
			if (_keyMatch.find(event.key.code) != _keyMatch.end())
				return _keyMatch[event.key.code];
		}
	}
	return NONE;
}

std::vector<std::string> N_LibOpengl::splitString(std::string str, char separator)
{
	std::string tmp = "";
	std::vector<std::string> splited;

	for (auto c: str) {
		if (c != separator)
			tmp += c;
		else if (c == separator && tmp != "") {
			splited.push_back(tmp);
			tmp = "";
		}
	}
	if (tmp != "")
		splited.push_back(tmp);
	return splited;
}

void N_LibOpengl::printScore(const std::vector<std::string> &games, std::size_t size, std::size_t _index)
{
	std::string _gameName = games[_index - size];
	int i = -5;
	int p = 0;

	std::ifstream readScore("scoreboard/" + _gameName + ".score");
	std::string line;
	std::string fileOutput;
	std::vector<std::string> split;
	std::vector<std::pair<int, std::string>> scoreboard;

	if (!readScore)
		return ;

	while (std::getline(readScore, line) && p < 10) {
		if (!line.empty()) {
			split = std::vector<std::string> (splitString(line, ':'));
			 if (split.size() == 2){
				 drawText(split[0], (getWidth() / 2) + split[0].size(), (getHeight() / 2) + i, GREEN);
				 drawText(split[1], (getWidth() / 2) + (split[0].size() + 10), (getHeight() / 2) + i, GREEN);
			 }
		}
		p = p + 1;
		i = i + 2;
	}
	readScore.close();
}

void N_LibOpengl::drawListLibs(const std::vector<std::string> &libs, int size_width, int size_height, std::size_t _index)
{
	int i = 0;
	std::size_t j = 0;
	Color color;

	for (auto c : libs) {
		if (_index == j) {
			color = RED;
			drawSquare((size_width / 3) - 5, (size_height / 3) + i, arcade::BG_RED);
		}
		else
			color = BLUE;
		drawText(c, (size_width / 3) + 0, (size_height / 3) + i, color);
		i += 5;
		j++;
	}
}

void N_LibOpengl::drawListGames(const std::vector<std::string> &games, std::size_t size, int size_width, int size_height, std::size_t _index)
{
	int i = 0;
	std::size_t j = size;
	Color color;

	for (auto c : games) {
		if (_index == j) {
			color = RED;
			drawSquare((size_width / 2) + (c.size() + 5), (size_height / 3) + i, arcade::BG_RED);
			printScore(games, size, _index);
		}
		else
			color = BLUE;
		drawText(c, (size_width / 2) + 0, (size_height / 3) + i, color);
		i += 5;
		j++;
	}
}

void N_LibOpengl::drawMenu(const std::vector<std::string> &libs, const std::vector<std::string> &games, std::size_t _index)
{
	drawText("      >>       >======>         >=>           >>       >====>      >=======> ", (getWidth() / 2) - 25, (getHeight() / 3) -7, RED);
	drawText("     >>=>      >=>    >=>    >=>   >=>      >>=>      >=>   >=>   >=>       ", (getWidth() / 2) - 25, (getHeight() / 3) - 6, GREEN);
	drawText("    >>  >=>     >=>    >=>   >=>            >> >=>     >=>    >=>  >=>       ", (getWidth() / 2) - 25, (getHeight() / 3) - 5, BLUE);
	drawText("   >=>  >=>    >> >==>      >=>            >=>  >=>    >=>    >=>  >=====>   ", (getWidth() / 2) - 25, (getHeight() / 3) - 4, YELLOW);
	drawText("  >===>>=>   >=>  >=>    >=>           >=====>>=>   >=>    >=>  >=>       ", (getWidth() / 2) - 25, (getHeight() / 3) - 3, CYAN);
	drawText(" >=>      >=>  >=>    >=>    >=>   >=>   >=>      >=>  >=>   >=>   >=>       ", (getWidth() / 2) - 25, (getHeight() / 3) - 2, WHITE);
	drawText(">=>          >=> >=>      >=>    >===>    >=>        >=> >====>      >=======> ", (getWidth() / 2) - 25, (getHeight() / 3) - 1, GREEN);
	drawListLibs(libs, (getWidth() / 2) + 5, getHeight() + 10, _index);
	drawListGames(games, libs.size(), (getWidth() / 2) + 25, getHeight() + 10, _index);
}

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibOpengl>();
}