//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Console
//

#include "Console.hpp"

using N_Console = arcade::Console;

N_Console::Console(const std::string &lib) :
	_libName(lib)
{}

N_Console::Console()
{}

N_Console::~Console()
{}

void N_Console::loadLibs(const std::string &path, Type type)
{
	DIR *dir;
	struct dirent *dp;
	std::string fileName;

	dir = opendir(path.c_str());
	if (dir == nullptr)
		throw std::runtime_error("Error: there isn't a " + path + " directory.");
	while ((dp = readdir(dir))) {
		fileName = dp->d_name;
		if (fileName.substr(fileName.find_last_of(".") + 1) == "so")
			type == LIBS ? _listLibs.push_back(fileName) : _listGames.push_back(fileName);
	}
}

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

void N_Console::drawBox()
{
	for (int i = 0; i < _lib->getWidth(); i++)
		_lib->drawSquare(i, 0);

	for (int i = 0; i < _lib->getWidth(); i++)
		_lib->drawSquare(i, _lib->getHeight());

	for (int i = 0; i < _lib->getHeight(); i++)
		_lib->drawSquare(0, i);

	for (int i = 0; i < _lib->getHeight(); i++)
		_lib->drawSquare(_lib->getWidth(), i);
}

void N_Console::writeMenu()
{
	_lib->openWindow();
	while (true) {
		_lib->clearWindow();
		drawBox();
		_lib->drawText("Welcome in Arcade", _lib->getWidth() / 2 - 17/2, 5);
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

void N_Console::showList()
{
	std::cout << "GAME" << std::endl;
	for (auto &c : _listGames)
		std::cout << c << std::endl;
	std::cout << "LIBS GRAPHICS" << std::endl;
	for (auto &c : _listLibs)
		std::cout << c << std::endl;
}