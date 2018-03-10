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
}

N_LibNcurses::~LibNcurses()
{
}

void N_LibNcurses::openWindow()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, true);
	getmaxyx(stdscr, _height, _width);
	start_color();
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
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
	mvprintw(y, x, "XX");
	attroff(COLOR_PAIR(color));
}

int N_LibNcurses::getHeight()
{
	return _height - 1;
}

int N_LibNcurses::getWidth()
{
	return _width - 1;
}

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibNcurses>();
}