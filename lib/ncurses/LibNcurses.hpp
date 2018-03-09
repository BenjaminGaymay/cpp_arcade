//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibNcurses
//

#pragma once

#include "ILibrary.hpp"
#include <iostream>

class LibNcurses : public ILibrary {
public:
	LibNcurses();
	~LibNcurses();

	void drawText(const std::string &, const int &x, const int &y) {};
	void refresh() {};
	void display(std::vector<std::vector<char>> &lol) {};
	void render() {};
	void processEvent() {};
};