//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Ghost
//

#pragma once

#include <chrono>
#include <vector>
#include <map>
#include <ncurses.h>

namespace arcade {
	class Ghost {
		public:
			Ghost (const char &c, const std::pair<int, int> &pos):
				_canMove(false), _x(0), _y(0), _prevChar(c),
				_lifeTime(std::chrono::system_clock::now()),  _pos(pos) {}
			bool canMove(std::vector<std::string>);
			void move(std::vector<std::string>);
			std::pair<int, int> choseSide(std::vector<std::string>);

			bool _canMove;
			int _x;
			int _y;
			char _prevChar;
			std::chrono::time_point<std::chrono::system_clock> _lifeTime;
			std::pair<int, int> _pos;
	};
}