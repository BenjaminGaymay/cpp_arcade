//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibSfml
//

#include <iostream>
#include "LibSfml.hpp"

LibSfml::LibSfml()
{
}

LibSfml::~LibSfml()
{
}

void LibSfml::drawText(const std::string &text, const int &x, const int &y)
{
	std::cout << "sfml " << text << std::endl;
}

void LibSfml::openWindow()
{
}

extern "C" std::unique_ptr<IGraphics> launch()
{
	return std::make_unique<LibSfml>();
}