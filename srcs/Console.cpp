//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Console
//

#include <unistd.h>
#include <chrono>
#include <thread>
#include "Console.hpp"

using N_Console = arcade::Console;

N_Console::Console(const std::string &lib) :
	_libName(lib)
{
	_state = IN_MENU;
}

N_Console::Console()
{}

N_Console::~Console()
{}

void N_Console::loadLibs(const std::string &path, Type type)
{
	DIR *dir;
	struct dirent *dp;
	std::string fileName;
	int i = 0;

	dir = opendir(path.c_str());
	if (dir == nullptr)
		throw std::runtime_error("Error: there isn't a " + path + " directory.");
	while ((dp = readdir(dir))) {
		fileName = dp->d_name;
		if (fileName.substr(fileName.find_last_of(".") + 1) == "so") {
			type == LIBS ? _listLibs.push_back(path + fileName) : _listGames.push_back(path + fileName);
		}
	}
	if (type == LIBS) {
		for (auto &c : _listLibs) {
			if (_libName == c)
				_currLib = i;
			++i;
		}
	} else
		_gameName = _listGames[0];
}

void N_Console::openLib(const Type &type)
{
	std::string lib = type == LIBS ? _libName : _gameName;

	std::cout << lib << std::endl;
	_handle = dlopen(lib.c_str(), RTLD_LAZY);
	char *err = dlerror();

	if (err)
		throw std::runtime_error("Error: lib: " + std::string(err));
	if (type == LIBS)
		_getLib = reinterpret_cast<std::unique_ptr<IGraphics>(*)()>(dlsym(_handle, "launch"));
	else
		_getGame = reinterpret_cast<std::unique_ptr<IGame>(*)()>(dlsym(_handle, "launch"));
	if ((err = dlerror()))
		throw std::runtime_error("Error: lib: " + std::string(err));
}

void N_Console::drawBox()
{
	for (int i = 0; i < _lib->getWidth(); i++)
		_lib->drawSquare(i, 0, arcade::BG_RED);

	for (int i = 0; i < _lib->getWidth(); i++)
		_lib->drawSquare(i, _lib->getHeight(), arcade::BG_RED);

	for (int i = 0; i < _lib->getHeight(); i++)
		_lib->drawSquare(0, i, arcade::BG_RED);

	for (int i = 0; i < _lib->getHeight(); i++)
		_lib->drawSquare(_lib->getWidth(), i, arcade::BG_RED);
}

void N_Console::drawListLibs()
{
	int i = 10;

	for (auto &c : _listLibs) {
		_lib->drawText(c,_lib->getWidth()/2 - c.size()/2 ,i, BLUE);
		i+=2;
	}
}

void N_Console::drawListGames()
{
	int i = 16;

	for (auto &c : _listGames) {
		_lib->drawText(c,_lib->getWidth() / 2 - c.size()/2 ,i, BLUE);
		i+=2;
	}
}

int N_Console::writeMenu()
{
	drawBox();
	drawListLibs();
	drawListGames();
	_lib->drawSquare(0, 0, BG_RED);
	_lib->drawText("Welcome in Arcade", _lib->getWidth() / 2 - 17/2, 5, GREEN);
	if (_key == ENTER)
		_state = IN_GAME;
	else if (_key == ESC)
		return Macro::EXIT;
	return Macro::SUCCESS;
}

void N_Console::loopConsole()
{
	_state = IN_MENU;

	_lib->openWindow();
	while (_lib->isOpen()) {
		_lib->clearWindow();
		if (_state == IN_MENU) {
			if (writeMenu() == Macro::EXIT)
				break;
		}
		else {
			_game->start(_lib);
			_game->setKey(_key);
			if (_key == ESC)
				_state = IN_MENU;
		}
		_key = _lib->getKey();
		_lib->refreshWindow();
	}
	_lib->closeWindow();
}

int N_Console::launch()
{
	try {
		openLib(arcade::Console::LIBS);
		openLib(arcade::Console::GAME);
		if (_getLib and _getGame) {
			_lib = _getLib();
			_game = _getGame();
		}
		else
			throw std::runtime_error("Error: lib: bad format of library.");
	} catch (std::runtime_error &e) {
		return std::cerr << e.what() << std::endl, Macro::ERROR;
	}
	loopConsole();
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

void N_Console::setGameName(const std::string &game)
{
	_gameName = game;
}

void N_Console::setLibName(const std::string &lib)
{
	_libName = lib;
}

const std::string &N_Console::getLibName() const
{
	return _libName;
}

const std::string &N_Console::getGameName() const
{
	return _gameName;
}