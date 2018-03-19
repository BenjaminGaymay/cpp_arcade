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
	_keyMatch[27] = ESC;
	_keyMatch[KEY_UP] = UP;
	_keyMatch[KEY_DOWN] = DOWN;
	_keyMatch[KEY_LEFT] = LEFT;
	_keyMatch[KEY_RIGHT] = RIGHT;
	_keyMatch[10] = ENTER;
	_keyMatch['p'] = PAUSE;
	_keyMatch['r'] = RESET;
}

N_LibNcurses::~LibNcurses()
{}

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
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_YELLOW, COLOR_BLACK);
	init_pair(9, COLOR_RED, COLOR_RED);
	init_pair(10, COLOR_BLUE, COLOR_BLUE);
	init_pair(11, COLOR_GREEN, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_WHITE);
	init_pair(13, COLOR_BLACK, COLOR_BLACK);
	init_pair(14, COLOR_CYAN, COLOR_CYAN);
	init_pair(15, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(16, COLOR_YELLOW, COLOR_YELLOW);

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
	int key = getch();

	if (_keyMatch.find(key) != _keyMatch.end())
		return _keyMatch[key];
	else
		return NONE;
}

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibNcurses>();
}