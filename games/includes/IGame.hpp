//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// IGame
//

#pragma once

#include <iostream>
#include <vector>
#include <map>

namespace arcade {
	class IGame {
	public:
		// IGame();
		// ~IGame();
		virtual std::vector<std::string> &getMap() = 0;
	protected:
		std::vector<std::string> _map;
	private:
	};
}