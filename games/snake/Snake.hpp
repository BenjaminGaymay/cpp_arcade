//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Snake
//

#pragma once

#include <chrono>
#include <algorithm>
#include <ncurses.h>
#include "IGame.hpp"

// #include "ncurses.hpp"

namespace arcade {
	class Snake : public IGame {
		public:
			int start(std::unique_ptr<arcade::IGraphics> &);
			void setKey(const Key &);
		public:
			Snake();
			void initMap();
			void initColor();
			void getNewSide();
			bool isWin();
			void moveSnake();
			void fillMap();
			void clearMap();
			void startChrono();
			bool doLoop();
			void addApple();
			bool checkApple(std::pair<std::size_t, std::size_t> &pos);
			void checkCollision(std::pair<std::size_t, std::size_t> &pos);
			void headSide(std::pair<int, int> const &);
			void bodySide(std::pair<int, int> &, std::pair<int, int> const &);

			std::vector<std::string> &getMap() { return _map; }
		private:
			std::vector<std::string> _map;
			int _x;
			int _y;
			std::vector<std::pair<std::size_t, std::size_t>> _snakePos;
			std::chrono::time_point<std::chrono::system_clock> _previousLoop;
			Key _key;
			bool _pause;
			int _score;
	};
}