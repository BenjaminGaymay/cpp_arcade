//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Console
//

#include "Console.hpp"
#include <chrono>
#include <thread>
using N_Console = Arcade::Console;

N_Console::Console(const std::string &lib) :
	_libName(lib)
{}

N_Console::Console()
{}

N_Console::~Console()
{}

N_Console &N_Console::setLib(const char *lib)
{
	_libName = lib;
	return *this;
}

const std::string &N_Console::getLib() const
{
	return _libName;
}

void N_Console::openLib()
{
	_handle = dlopen(_libName.c_str(), RTLD_LAZY);
	char *err = dlerror();
	if (err)
		throw std::runtime_error("Error: lib: " + std::string(err));
}

void N_Console::writeMenu()
{
	_lib->drawText("pd", 5, 5);
	_lib->openWindow();
	// while (true) {
	// 	_lib->clear();
	// 	_lib->refresh();
	// }
	for (int i = 0; i < 5000; i++) {
		_lib->clearWindow();
		_lib->refreshWindow();
	}
	_lib->closeWindow();
}

int N_Console::launch()
{
	create = reinterpret_cast<std::unique_ptr<IGraphics>(*)()>(dlsym(_handle, "launch"));
	try {
		if (create)
			_lib = create();
		else
			throw std::runtime_error("Error: lib: bad format of library.");
	} catch (std::runtime_error &e) {
		return std::cerr << e.what() << std::endl, Macro::ERROR;
	}
	writeMenu();
	return Macro::SUCCESS;
}