//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// snake
//

#pragma once

#include "IGame.hpp"
#include "ncurses.hpp"

namespace arcade {
	class Snake : public IGame {
		public:
			Snake():
				_x(1), _y(0)  {};
			void initMap();
			void initColor();
			void getNewSide();
			void moveSnake();
			void fillMap();
			void clearMap();
			void startChrono();
			bool doLoop();
			void addApple();
			bool checkApple(std::pair<std::size_t, std::size_t> &pos);
			void checkCollision(std::pair<std::size_t, std::size_t> &pos);

			std::vector<std::string> &getMap() { return _map; }
		private:
			int _x;
			int _y;
			std::vector<std::pair<std::size_t, std::size_t>> _snakePos;
			std::vector<std::pair<std::size_t, std::size_t>> _applePos;
			std::chrono::time_point<std::chrono::system_clock> _previousLoop;
	};
}