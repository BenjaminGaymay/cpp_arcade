//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// IGame
//

#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "IGraphics.hpp"

namespace arcade {
	class IGame {
	public:
		~IGame() {};
		virtual void start(std::unique_ptr<arcade::IGraphics> &) = 0;
		virtual void setKey(const Key &) = 0;
	};
}