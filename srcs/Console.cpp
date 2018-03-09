//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Console
//

#include "Console.hpp"

using N_Console = Arcade::Console;

N_Console::Console(const std::string &lib) :
	_lib(lib)
{}

N_Console::Console()
{}

N_Console::~Console()
{}

N_Console &N_Console::setLib(const char *lib)
{
	_lib = lib;
	return *this;
}

const std::string &N_Console::getLib() const
{
	return _lib;
}

void N_Console::openLib()
{
	_handle = dlopen(_lib.c_str(), RTLD_LAZY);

	if (dlerror() != NULL)
		throw std::runtime_error("Error: lib: bad library path");
}

void N_Console::launch()
{
	lol = reinterpret_cast<int(*)(int,int)>(dlsym(_handle, "addnb"));
	std::cout << lol(5,5) << std::endl;
	// pouet = reinterpret_cast<(test::*)(int,int)>(dlsym(_handle, "addnb"));
}