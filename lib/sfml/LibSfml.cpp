//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibSfml
//

#include <iostream>
#include "LibSfml.hpp"


using N_LibSfml = arcade::LibSfml;

N_LibSfml::LibSfml()
{
}

N_LibSfml::~LibSfml()
{
}

void N_LibSfml::drawText(const std::string &text, const int &x, const int &y)
{
	std::cout << "sfml " << text << std::endl;
}

void N_LibSfml::openWindow()
{
}

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibSfml>();
}