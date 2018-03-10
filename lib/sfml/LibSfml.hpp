//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibSfml
//

#pragma once

#include "IGraphics.hpp"

namespace arcade {
	class LibSfml : public IGraphics {
	public:
		LibSfml();
		~LibSfml();

		void drawText(const std::string &, const int &, const int &);
		void drawSquare(const int &, const int &) {};
		void clearWindow() {};
		void refreshWindow() {};
		void display(std::vector<std::string> &lol) {};
		void render() {};
		void getKey() {};
		void closeWindow() {};
		void openWindow();
		int getWidth() {};
		int getHeight() {};
	};
}