//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// ILibrary
//

#pragma once

#include <memory>

class ILibrary {
public:
	virtual ~ILibrary() {};
	virtual void launch() = 0;
};