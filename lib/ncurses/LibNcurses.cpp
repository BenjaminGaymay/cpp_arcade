//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibNcurses
//

#include "LibNcurses.hpp"

using N_LibNcurses = arcade::LibNcurses;

N_LibNcurses::LibNcurses()
{
	_keyMatch['a'] = ESC;
	_keyMatch['z'] = UP;
	_keyMatch['s'] = DOWN;
	_keyMatch['q'] = LEFT;
	_keyMatch['d'] = RIGHT;
	_keyMatch['e'] = ENTER;
	_keyMatch['p'] = PAUSE;
	_keyMatch['r'] = RESET;
}

N_LibNcurses::~LibNcurses()
{
}

void N_LibNcurses::openWindow()
{
	initscr();
	nodelay(stdscr, TRUE);
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, _height, _width);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_RED);
	init_pair(5, COLOR_BLUE, COLOR_BLUE);
	init_pair(6, COLOR_GREEN, COLOR_GREEN);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_WHITE, COLOR_WHITE);
	init_pair(9, COLOR_BLACK, COLOR_BLACK);
}

bool N_LibNcurses::isOpen()
{
	return true;
}

void N_LibNcurses::closeWindow()
{
	endwin();
}

void N_LibNcurses::clearWindow()
{
	clear();
}

void N_LibNcurses::refreshWindow()
{
	refresh();
}

void N_LibNcurses::drawText(const std::string &text, const int &x, const int &y, const Color &color)
{
	attron(COLOR_PAIR(color));
	mvprintw(y, x, "%s", text.c_str());
	attroff(COLOR_PAIR(color));
}

arcade::Color N_LibNcurses::setColor(char c)
{
	switch (c) {
		case 'W':
			return arcade::BG_WHITE;
		case 'G':
			return arcade::BG_GREEN;
		case 'R':
			return arcade::BG_RED;
		case 'B':
			return arcade::BG_BLUE;
		case 'Y':
			return arcade::BG_RED;
		default:
			return arcade::BG_BLACK;
	}
}

void N_LibNcurses::drawMap(const std::vector<std::string> &map)
{
	arcade::Color color;

	for (unsigned i = 0 ; i < map.size() ; i++) {
		for (unsigned j = 0 ; j < (map[i].size() * 2) ; j++) {
			color = setColor(map[i][j / 2]);
			drawSquare(getWidth() / 2 - (map[i].size() - 1) + j, getHeight() / 2 - (map.size() / 2) + i, color);
		}
	}
}

void N_LibNcurses::drawSquare(const int &x, const int &y, const Color &color)
{
	attron(COLOR_PAIR(color));
	mvprintw(y, x, "X");
	attroff(COLOR_PAIR(color));
}

int N_LibNcurses::getHeight()
{
	return _height;
}

int N_LibNcurses::getWidth()
{
	return _width;
}

arcade::Key N_LibNcurses::getKey()
{
	char key = getch();

	if (_keyMatch.find(key) != _keyMatch.end())
		return _keyMatch[key];
	else
		return NONE;
}

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibNcurses>();
}