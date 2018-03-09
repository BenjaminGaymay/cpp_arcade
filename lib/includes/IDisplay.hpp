//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// IDisplay
//

#pragma once

#include <memory>
#include <vector>

class IDisplay {
public:
	virtual ~IDisplay() {};

	virtual void drawText(const std::string &, const int &, const int &) = 0;
	virtual void refresh() = 0;
	virtual void display(std::vector<std::vector<char>> &) = 0;
	virtual void render() = 0;
	virtual void processEvent() = 0;
	virtual void closeWindow() = 0;
};