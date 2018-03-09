//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibNcurses
//

#pragma once

#include <iostream>
#include <ncurses.h>
#include "IGraphics.hpp"

class LibNcurses : public IGraphics {
public:
	LibNcurses();
	~LibNcurses();

	void drawText(const std::string &, const int &x, const int &y);
	void clearWindow();
	void refreshWindow();
	void display(std::vector<std::vector<char>> &lol) {};
	void getKey() {};
	void closeWindow();
	void openWindow();

private:
	WINDOW *_window;
};