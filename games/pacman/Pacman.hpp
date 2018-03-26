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
#include "Ghost.hpp"

namespace arcade {
	enum PacmanState {
		SUPER,
		NORMAL
	};

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
			void moveGhosts();
			void fillMap();
			void clearMap();
			void startChrono();
			bool doLoop();
			bool checkGhostCollision();
			void manageSuperMod(std::pair<int, int> &);
			std::vector<std::string> &getMap() { return _map; }
			void refreshPCPos();

		private:
			std::vector<std::string> _map;
			int _x;
			int _y;
			std::pair<int, int> _pacmanPos;
			PacmanState _state;
			std::vector<std::unique_ptr<Ghost>> _ghostPos;
			std::chrono::time_point<std::chrono::system_clock> _previousLoop;
			std::chrono::time_point<std::chrono::system_clock> _superMod;
			Key _key;
			bool _pause;
			int _score;
	};
}