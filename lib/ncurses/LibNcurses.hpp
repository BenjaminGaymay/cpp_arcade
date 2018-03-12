//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibNcurses
//

#pragma once

#include <iostream>
#include <ncurses.h>
#include <map>
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
		Key getKey();
		void closeWindow();
		void openWindow();
		int getHeight();
		int getWidth();
		bool isOpen();

	private:
		int _width;
		int _height;

		std::map<char, Key> _keyMatch;
	};
}