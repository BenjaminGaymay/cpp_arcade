//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// IGraphics
//

#pragma once

#include <memory>
#include <vector>

class IGraphics {
public:
	virtual ~IGraphics() {};

	virtual void drawText(const std::string &, const int &, const int &) = 0;
	virtual void clearWindow() = 0;
	virtual void refreshWindow() = 0;
	virtual void display(std::vector<std::vector<char>> &) = 0;
	virtual void getKey() = 0;
	virtual void closeWindow() = 0;
	virtual void openWindow() = 0;
};