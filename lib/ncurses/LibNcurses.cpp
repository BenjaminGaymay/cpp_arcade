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

extern "C" std::unique_ptr<ILibrary> create()
{
	return std::make_unique<LibNcurses>();
}