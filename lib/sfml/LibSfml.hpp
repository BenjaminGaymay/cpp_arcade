//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibSfml
//

#pragma once

#include "IDisplay.hpp"

class LibSfml : public IDisplay {
public:
	LibSfml();
	~LibSfml();

	void drawText(const std::string &, const int &, const int &) {};
	void refresh() {};
	void display(std::vector<std::vector<char>> &lol) {};
	void render() {};
	void processEvent() {};
	void closeWindow() {};
};