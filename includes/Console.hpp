//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Console
//

#pragma once

#include <iostream>
#include <dlfcn.h>

namespace Arcade {
	class Console {
	public:
		Console(const std::string &);
		Console();
		~Console();
		void openLib();
		Console &setLib(const char *);
		const std::string &getLib() const;
		void launch();
	private:
		std::string _lib;
		void *_handle;
		int (*lol)(int, int);
		// int pouet(test::*)(int,int);
	};
}