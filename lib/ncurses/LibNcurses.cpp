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

void N_LibNcurses::drawSquare(const int &x, const int &y, const Color &color)
{
	attron(COLOR_PAIR(color));
	mvprintw(y, x * 2, "XX");
	attroff(COLOR_PAIR(color));
}

int N_LibNcurses::getHeight()
{
	return _height - 1;
}

int N_LibNcurses::getWidth()
{
	return _width - 2;
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