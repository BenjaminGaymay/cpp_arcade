//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibNcurses
//

#pragma once

#include "IDisplay.hpp"
#include <iostream>

class LibNcurses : public IDisplay {
public:
	LibNcurses();
	~LibNcurses();

	void drawText(const std::string &, const int &x, const int &y) {};
	void refresh() {};
	void display(std::vector<std::vector<char>> &lol) {};
	void render() {};
	void processEvent() {};
	void closeWindow() {};
};