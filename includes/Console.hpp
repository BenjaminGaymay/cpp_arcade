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
#include "IGraphics.hpp"
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
		void writeMenu();
	private:
		std::string _libName;
		void *_handle;
		std::unique_ptr<IGraphics> (*create)();
		std::unique_ptr<IGraphics> _lib;
		// int pouet(test::*)(int,int);
	};
}