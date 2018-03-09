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
		throw std::runtime_error("Error: lib: bad library path or the file isn't a library.");
}

int N_Console::launch()
{
	create = reinterpret_cast<std::unique_ptr<IDisplay>(*)()>(dlsym(_handle, "launch"));
	try {
		if (create)
			_game = create();
		else
			throw std::runtime_error("Error: lib: bad format of library.");
	} catch (std::runtime_error &e) {
		return std::cerr << e.what() << std::endl, Macro::ERROR;
	}
}