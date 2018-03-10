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

namespace arcade {
	class LibNcurses : public IGraphics {
	public:
		LibNcurses();
		~LibNcurses();

		void drawText(const std::string &, const int &x, const int &y, const Color &);
		void drawSquare(const int &, const int &, const Color &);
		void clearWindow();
		void refreshWindow();
		void display(std::vector<std::string> &lol) {};
		void getKey() {};
		void closeWindow();
		void openWindow();
		int getHeight();
		int getWidth();

	private:
		int _width;
		int _height;
	};
}