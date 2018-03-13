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
	enum Color {
		RED = 1,
		BLUE,
		GREEN,
		BG_RED,
		BG_BLUE,
		BG_GREEN,
		WHITE,
		BG_WHITE,
		BG_BLACK,
		APPLE,
		GRASS,
		BRICK
	};

	enum Key {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ESC,
		ENTER,
		PAUSE,
		RESET,
		NONE
	};
	class IGraphics {
	public:
		virtual ~IGraphics() {};

		virtual void drawText(const std::string &, const int &, const int &, const Color &) = 0;
		virtual void drawSquare(const int &, const int &, const Color &) = 0;
		virtual void drawMap(const std::vector<std::string> &) = 0;
		virtual Color setColor(char) = 0;
		virtual void clearWindow() = 0;
		virtual void refreshWindow() = 0;
		virtual Key getKey() = 0;
		virtual void closeWindow() = 0;
		virtual void openWindow() = 0;
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual bool isOpen() = 0;
	};
}