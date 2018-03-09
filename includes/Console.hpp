//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Console
//

#pragma once

#include <memory>
#include <iostream>
#include <dlfcn.h>
#include "IDisplay.hpp"
#include "Macro.hpp"

namespace Arcade {
	class Console {
	public:
		Console(const std::string &);
		Console();
		~Console();
		void openLib();
		Console &setLib(const char *);
		const std::string &getLib() const;
		int launch();
	private:
		std::string _lib;
		void *_handle;
		std::unique_ptr<IDisplay> (*create)();
		std::unique_ptr<IDisplay> _game;
		// int pouet(test::*)(int,int);
	};
}