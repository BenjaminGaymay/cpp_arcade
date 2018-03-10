//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// IGraphics
//

#pragma once

#include <memory>
#include <vector>

namespace arcade {
	class IGraphics {
	public:
		virtual ~IGraphics() {};

		virtual void drawText(const std::string &, const int &, const int &) = 0;
		virtual void drawSquare(const int &, const int &) = 0;
		virtual void clearWindow() = 0;
		virtual void refreshWindow() = 0;
		virtual void display(std::vector<std::string> &) = 0;
		virtual void getKey() = 0;
		virtual void closeWindow() = 0;
		virtual void openWindow() = 0;
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
	};
}