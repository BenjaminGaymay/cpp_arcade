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
	std::cout << "ncurses " << text << std::endl;
}

void LibNcurses::openWindow()
{
	initscr();
	cbreak();
	noecho();
	timeout(0);
	keypad(stdscr, true);
	_window = newwin(50,50,0,0);
}

void LibNcurses::closeWindow()
{
	delwin(_window);
	endwin();
}

void LibNcurses::clearWindow()
{
	clear();
}

void LibNcurses::refreshWindow()
{
	refresh();
}

extern "C" std::unique_ptr<IGraphics> launch()
{
	return std::make_unique<LibNcurses>();
}