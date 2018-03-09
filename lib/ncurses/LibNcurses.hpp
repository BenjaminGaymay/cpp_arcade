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
	void launch() {
		std::cout << "pd" << std::endl;
		return;
	}
};