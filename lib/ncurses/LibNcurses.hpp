//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibNcurses
//

#pragma once

#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <memory>
#include <map>
#include <dlfcn.h>
#include <dirent.h>
#include "IGraphics.hpp"

namespace arcade {
	class LibNcurses : public IGraphics {
	public:
		LibNcurses();
		~LibNcurses();

		void drawText(const std::string &, const int &x, const int &y, const Color &);
		void drawSquare(const int &, const int &, const Color &);
		void drawMap(const std::vector<std::string> &);
		arcade::Color setColor(char);
		void clearWindow();
		void refreshWindow();
		Key getKey();
		void closeWindow();
		void openWindow();
		int getHeight();
		std::vector<std::string> splitString(std::string , char );
		int getWidth();
		bool isOpen();
		void drawMenu(const std::vector<std::string> &, const std::vector<std::string> &, std::size_t);
		void printScore(const std::vector<std::string> &, std::size_t, std::size_t);
		void drawListLibs(const std::vector<std::string> &, int , int , std::size_t );
		void drawListGames(const std::vector<std::string> &, std::size_t, int , int , std::size_t );
	private:
		int _width;
		int _height;

		std::map<int, Key> _keyMatch;
	};
}