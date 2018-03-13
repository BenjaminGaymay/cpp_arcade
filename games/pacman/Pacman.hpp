//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Pacman
//

#pragma once

#include <chrono>
#include <algorithm>
#include <ncurses.h>
#include "IGame.hpp"

// #include "ncurses.hpp"

namespace arcade {
	class Pacman : public IGame {
		public:
			void start(std::unique_ptr<arcade::IGraphics> &);
			void setKey(const Key &);
		public:
			Pacman();
			void initMap();
			void initColor();
			void getNewSide();
			void movePacman();
			void fillMap();
			void clearMap();
			void startChrono();
			bool doLoop();
			std::vector<std::string> &getMap() { return _map; }
		private:
			std::vector<std::string> _map;
			int _x;
			int _y;
			std::pair<int, int> _pacmanPos;
			std::chrono::time_point<std::chrono::system_clock> _previousLoop;
			Key _key;
			bool _pause;
	};
}