//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibNcurses
//

#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <dlfcn.h>
#include <dirent.h>
#include <fstream>
#include <ncurses.h>
#include <map>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "IGraphics.hpp"

namespace arcade {
	class LibAllegro : public IGraphics {
	public:
		LibAllegro();
		~LibAllegro();

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
		int getWidth();
		std::vector<std::string> splitString(std::string , char );
		void printScore(const std::vector<std::string> &, const std::vector<std::string> &, std::size_t);
		int getScaleHeight();
		std::string epureName(const std::string &);
		void drawListLibs(const std::vector<std::string> &, const std::vector<std::string> &, int , int , std::size_t );
		void drawListGames(const std::vector<std::string> &, const std::vector<std::string> &, int , int , std::size_t );
		void drawMenu(const std::vector<std::string> &, const std::vector<std::string> &, std::size_t);
		int getScaleWidth();
		bool isOpen();

	private:
		int _width;
		int _height;
		int _sx;
		int _sy;
		float _fps;

		ALLEGRO_DISPLAY *_window;
		ALLEGRO_FONT *_font;
		ALLEGRO_EVENT_QUEUE *_eventQueue;
		ALLEGRO_TIMER *_timer;
		ALLEGRO_BITMAP *_background;
		ALLEGRO_EVENT _event;

		std::map<int, Key> _keyMatch;
		std::map<Color, ALLEGRO_COLOR> _colorsMatch;
	};
}