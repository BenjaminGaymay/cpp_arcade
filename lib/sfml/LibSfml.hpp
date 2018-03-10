//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibSfml
//

#pragma once

#include "IGraphics.hpp"

class LibSfml : public IGraphics {
public:
	LibSfml();
	~LibSfml();

	void drawText(const std::string &, const int &, const int &);
	void drawSquare(const int &, const int &) {};
	void clearWindow() {};
	void refreshWindow() {};
	void display(std::vector<std::vector<char>> &lol) {};
	void render() {};
	void getKey() {};
	void closeWindow() {};
	void openWindow();
};