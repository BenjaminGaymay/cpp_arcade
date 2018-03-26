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
#include "Path.hpp"

namespace arcade {
	enum GhostState {
		ALIVE,
		EATABLE,
		DEAD
	};

	class Ghost {
		public:
			Ghost (const char &, const std::pair<int, int> &);
			bool canMove(std::vector<std::string>);
			void move(std::vector<std::string>);
			std::pair<int, int> choseSide(std::vector<std::string>);
			void setPacMan(const Pos &);
			void setPacMan(const std::pair<int, int> &);

			bool _canMove;
			int _x;
			int _y;
			char _prevChar;
			GhostState _state;
			std::pair<int, int> _pos;
			Pos _pacmanPos;
			std::chrono::time_point<std::chrono::system_clock> _lifeTime;
			std::chrono::time_point<std::chrono::system_clock> _deadTime;
	};
}