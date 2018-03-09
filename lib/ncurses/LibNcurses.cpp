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

extern "C" std::unique_ptr<IGraphics> launch()
{
	return std::make_unique<LibNcurses>();
}