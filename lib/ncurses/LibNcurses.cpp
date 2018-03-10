//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibNcurses
//

#include "LibNcurses.hpp"

LibNcurses::LibNcurses()
{
}

LibNcurses::~LibNcurses()
{
}


void LibNcurses::drawText(const std::string &text, const int &x, const int &y)
{
	mvprintw(x, y, "%s", text.c_str());
}

void LibNcurses::openWindow()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, true);
	start_color();
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);
	init_pair(3, COLOR_GREEN, COLOR_GREEN);
}

void LibNcurses::closeWindow()
{
	endwin();
}

void LibNcurses::clearWindow()
{
	clear();
}

void LibNcurses::refreshWindow()
{
	refresh();
	wrefresh(_window);
}

void LibNcurses::drawSquare(const int &x, const int &y)
{
	attron(COLOR_PAIR(1));
	mvprintw(x, y, "XX");
	attroff(COLOR_PAIR(1));
}

extern "C" std::unique_ptr<IGraphics> launch()
{
	return std::make_unique<LibNcurses>();
}