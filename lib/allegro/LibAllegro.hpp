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
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
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
		bool isOpen();

	private:
		int _width;
		int _height;
		int _sx;
		int _sy;

		ALLEGRO_DISPLAY *_window;
		ALLEGRO_FONT *_font;
		ALLEGRO_EVENT_QUEUE *_eventQueue;

		std::map<int, Key> _keyMatch;
		std::map<Color, ALLEGRO_COLOR> _colorsMatch;
	};
}