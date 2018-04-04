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
		WHITE,
		BLACK,
		CYAN,
		MAGENTA,
		YELLOW,

		BG_RED,
		BG_BLUE,
		BG_GREEN,
		BG_WHITE,
		BG_BLACK,
		BG_CYAN,
		BG_MAGENTA,
		BG_YELLOW,

		APPLE,
		GRASS,
		BRICK,
		BRICK_HEAD,
		GUM,
		WOOD,

		HEAD_RIGHT,
		HEAD_LEFT,
		HEAD_TOP,
		HEAD_DOWN,

		BODY_RIGHT,
		BODY_LEFT,
		BODY_TOP,
		BODY_DOWN,

		SHEAD_RIGHT,
		SHEAD_LEFT,
		SHEAD_TOP,
		SHEAD_DOWN,

		SUPERGUM,

		G_GREEN,
		G_PINK,
		G_BLUE,
		G_RED,
		G_DEAD
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
		NONE,
		SHOOT,
		NEXT_LIB,
		PREVIOUS_LIB,
		NEXT_GAME,
		PREVIOUS_GAME
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
		virtual void printScore(const std::vector<std::string> &, const std::vector<std::string> &, std::size_t) = 0;
		virtual Key getKey() = 0;
		virtual void closeWindow() = 0;
		virtual void openWindow() = 0;
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual std::vector<std::string> splitString(std::string , char ) = 0;
		virtual bool isOpen() = 0;
		virtual void drawMenu(const std::vector<std::string> &, const std::vector<std::string> &, std::size_t) = 0;
		virtual std::string epureName(const std::string &) = 0;
		virtual void drawListLibs(const std::vector<std::string> &, const std::vector<std::string> &, int , int , std::size_t ) = 0;
		virtual void drawListGames(const std::vector<std::string> &, const std::vector<std::string> &, int , int , std::size_t ) = 0;
	};
}