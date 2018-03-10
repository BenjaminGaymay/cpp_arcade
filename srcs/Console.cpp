//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Console
//

#include <chrono>
#include <thread>
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
	for (auto &c : _listLibs) {
		if (_libName == c)
			_currLib = i;
		++i;
	}
}

void N_Console::setLibName(const char *lib)
{
	_libName = lib;
}

const std::string &N_Console::getLibName() const
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
		_lib->drawSquare(i, 0, arcade::IGraphics::BG_RED);

	for (int i = 0; i < _lib->getWidth(); i++)
		_lib->drawSquare(i, _lib->getHeight(), arcade::IGraphics::BG_RED);

	for (int i = 0; i < _lib->getHeight(); i++)
		_lib->drawSquare(0, i, arcade::IGraphics::BG_RED);

	for (int i = 0; i < _lib->getHeight(); i++)
		_lib->drawSquare(_lib->getWidth(), i, arcade::IGraphics::BG_RED);
}

void N_Console::drawListLibs()
{
	int i = 10;

	for (auto &c : _listLibs) {
		_lib->drawText(c,_lib->getWidth()/2 - c.size()/2 ,i, IGraphics::BLUE);
		i+=2;
	}
}

void N_Console::drawListGames()
{
	int i = 16;

	for (auto &c : _listGames) {
		_lib->drawText(c,_lib->getWidth() / 2 - c.size()/2 ,i, IGraphics::BLUE);
		i+=2;
	}
}

void N_Console::writeMenu()
{
	_lib->openWindow();

	while (true) {
		_lib->clearWindow();
		drawBox();
		drawListLibs();
		drawListGames();
		if (_lib->getKey() == arcade::IGraphics::ESC) {
			_lib->closeWindow();
			break;
		}
		for (int i = _lib->getWidth()/3;i < _lib->getWidth()*2/3; i++){
			_lib->drawSquare(i, 3, arcade::IGraphics::BG_RED);
			_lib->drawSquare(i, 7, arcade::IGraphics::BG_RED);
			_lib->drawSquare(i, 14, arcade::IGraphics::BG_RED);
			_lib->drawSquare(i, 18, arcade::IGraphics::BG_RED);
		}
		_lib->drawText("Welcome in Arcade", _lib->getWidth() / 2 - 17/2, 5, IGraphics::GREEN);
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