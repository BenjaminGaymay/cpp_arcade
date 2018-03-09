//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ILibrary
//

#pragma once

#include <memory>
#include <vector>

class ILibrary {
public:
	virtual ~ILibrary() {};

	virtual void drawText(const std::string &, const int &, const int &) = 0;
	virtual void refresh() = 0;
	virtual void display(std::vector<std::vector<char>> &) = 0;
	virtual void render() = 0;
	virtual void processEvent() = 0;
};