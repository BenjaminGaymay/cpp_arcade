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
	_currGame = 0;
	_currLib = 0;
	_pseudo = "Bertrand";
}

N_Console::Console()
{
	_state = IN_MENU;
	_currGame = 0;
	_currLib = 0;
	_pseudo = "Bertrand";
}

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
		_gameName = _listGames[_currGame];
}

std::string N_Console::epureName(const std::string &name)
{
	std::string str(name);

	std::size_t pos = str.find_last_of("_") + 1;
	std::size_t end = str.find_last_of(".");
	return str.substr(pos, end - pos);
}

void N_Console::openLib(const Type &type)
{
	std::string lib = type == LIBS ? _libName : _gameName;
	char *err;

	_handle = dlopen(lib.c_str(), RTLD_LAZY);
	err = dlerror();
	if (err)
		throw std::runtime_error("Error: lib: " + std::string(err));
	if (type == LIBS)
		_getLib = reinterpret_cast<std::unique_ptr<IGraphics>(*)()>(dlsym(_handle, "launch"));
	else
		_getGame = reinterpret_cast<std::unique_ptr<IGame>(*)()>(dlsym(_handle, "launch"));
	err = dlerror();
	if (err)
		throw std::runtime_error("Error: lib: " + std::string(err));
}

void N_Console::drawBox(int size_width, int size_height, int bonus)
{
	for (int i = ((size_width / 3) - bonus) ; i <= (size_width + bonus) - (size_width / 3); i++) {
		_lib->drawSquare(i, size_height / 3 - bonus, arcade::BG_RED);
		_lib->drawSquare(i, size_height - (size_height / 3) + bonus, arcade::BG_RED);
	}
	for (int i = ((size_height / 3) - bonus); i <= (size_height + bonus) - (size_height / 3); i++) {
		_lib->drawSquare(size_width - (size_width / 3) + bonus, i, arcade::BG_RED);
		_lib->drawSquare(size_width / 3 - bonus, i, arcade::BG_RED);
	}
}

void N_Console::drawListLibs(int i, int size_width, int size_height, int bonus)
{
	std::size_t j = 0;
	Color color;

	for (auto c : _listLibs) {
		c = epureName(c);
		if (_currLib == j)
			color = GREEN;
		else
			color = BLUE;
		_lib->drawText(c, (size_width / 3) + bonus, (size_height / 3) + i, color);
		i+=2;
		j++;
	}
}
void N_Console::drawListGames(int i, int size_width, int size_height, int bonus)

{
	std::size_t j = _listLibs.size();

	Color color;
	for (auto c : _listGames) {
		c = epureName(c);
		if (_currLib == j)
			color = GREEN;
		else
			color = BLUE;
		_lib->drawText(c, (size_width / 2) + bonus, (size_height / 3) + i, color);
		i+=2;
		j++;
	}
}

void N_Console::enterAction()
{
	if (_currLib < _listLibs.size()) {
		_lib->closeWindow();
		_libName = _listLibs[_currLib];
		try {
			openLib(LIBS);
		} catch (std::runtime_error &e) {
			throw e;
		}
		_lib = _getLib();
		_lib->openWindow();
	} else {
		_gameName = _listGames[_currGame];
		try {
			openLib(GAME);
		} catch (std::runtime_error &e) {
			throw e;
		}
		changeLibs(GAME);
		_state = IN_GAME;
	}
}

void N_Console::upAction()
{
	_currLib = (_currLib == 0 ? 0 : _currLib - 1);
	if (_currLib >= _listLibs.size())
		_currGame--;
}

void N_Console::downAction()
{
	_currLib = (_currLib == (_listGames.size() + _listLibs.size()) - 1 ? (_listGames.size() + _listLibs.size()) - 1 : _currLib + 1);
	// _currLib = _currLib == _listLibs.size() - 1 ? _currLib : _currLib + 1;
	if (_currLib > _listLibs.size())
		_currGame = (_listGames.size() - 1 == _currGame ? _listGames.size() - 1 : _currGame + 1);
}

void N_Console::drawLibs()
{
	if(_libName == "./lib/lib_arcade_ncurses.so"){
		drawBox(_lib->getWidth(),_lib->getHeight(), 3);
		drawListLibs(6,_lib->getWidth(),_lib->getHeight(),10);
		drawListGames(6,_lib->getWidth(),_lib->getHeight(),10);
		_lib->drawText("PORCHERT BIG BOSS", (_lib->getWidth() / 3) + 10, (_lib->getHeight() / 3) + 2, GREEN);
	}
	else if(_libName == "./lib/lib_arcade_sfml.so"){
		drawBox(62,35, 2);
		drawListLibs(6,45,28,10);
		drawListGames(6,45,28,10);
		_lib->drawText("PORCHERT BIG BOSS", (45 / 3) + 10, (30 / 3) + 2, GREEN);
	}
	else if(_libName == "./lib/lib_arcade_allegro.so"){
		drawBox(62,35, 2);
		drawListLibs(6,49,28,10);
		drawListGames(6,49,28,10);
		_lib->drawText("PORCHERT BIG BOSS", (62 / 3) + 10, (30 / 3) + 2, GREEN);
	}
	else{
		drawBox(_lib->getWidth(),_lib->getHeight(), 10);
		drawListLibs(6,_lib->getWidth(),_lib->getHeight(),10);
		drawListGames(6,_lib->getWidth(),_lib->getHeight(),10);
		_lib->drawText("PORCHERT BIG BOSS", (_lib->getWidth() / 3) + 10, (_lib->getHeight() / 3) + 2, GREEN);
	}
}

int N_Console::writeMenu()
{
	drawLibs();
	switch (_key) {
		case ENTER:
			enterAction();
			break;
		case ESC:
			return Macro::EXIT;
		case UP:
			upAction();
			break;
		case DOWN:
			downAction();
			break;
		default:
			break;
	}
	return Macro::SUCCESS;
}

void N_Console::setScore(const int score)
{
	auto game = epureName(_gameName);

	std::ifstream readScore("scoreboard/" + game + ".score");
	std::string line;
	std::string fileOutput;
	std::vector<std::string> split;
	std::vector<std::pair<int, std::string>> scoreboard;

	if (! readScore)
		return ;

	while (std::getline(readScore, line)) {
		if (! line.empty()) {
			split = ManageStrings::splitString(line, ':');
			if (split.size() == 2)
				scoreboard.push_back({std::atoi(split[1].c_str()), split[0]});
		}
	}
	readScore.close();

	scoreboard.push_back({score, _pseudo});
	std::sort(scoreboard.begin(), scoreboard.end());
	std::reverse(scoreboard.begin(), scoreboard.end());
	if (scoreboard.size() > 10)
		scoreboard.erase(scoreboard.begin() + 10, scoreboard.end());

	std::ofstream writeScore("scoreboard/" + game + ".score");
	if (! writeScore)
		return ;

	for (auto &result : scoreboard)
		writeScore << result.second << ':' << std::to_string(result.first) << std::endl;

	writeScore.close();
}

void N_Console::handleKeys()
{
	if (_key == NEXT_LIB or _key == PREVIOUS_LIB) {
		_lib->closeWindow();
		if (_key == NEXT_LIB)
			_currLib = _currLib >= _listLibs.size() - 1 ? 0 : _currLib + 1;
		else
			_currLib = _currLib == 0 ? _listLibs.size() - 1 : _currLib - 1;
		_libName = _listLibs[_currLib];
		try {
			openLib(LIBS);
		} catch (std::exception &e) {
			throw e;
		}
		changeLibs(LIBS);
		_lib->openWindow();
	}
	if (_state == IN_GAME and (_key == NEXT_GAME or _key == PREVIOUS_GAME)) {
		if (_key == NEXT_GAME)
			_currGame = _currGame == _listGames.size() - 1 ? 0 : _currGame + 1;
		else
			_currGame = _currGame == 0 ? _listGames.size() - 1 : _currGame - 1;
		_gameName = _listGames[_currGame];
		try {
			openLib(GAME);
		} catch (std::exception &e) {
			throw e;
		}
		changeLibs(GAME);
	}
}

void N_Console::loopConsole()
{
	unsigned highscore = 0;
	unsigned score;

	_lib->openWindow();
	while (_lib->isOpen()) {
		_lib->clearWindow();
		if (_state == IN_MENU) {
			if (writeMenu() == Macro::EXIT)
				break;
		}
		else {
			score = _game->start(_lib);
			if (score > highscore)
				highscore = score;
			_game->setKey(_key);
			if (_key == ESC or _game->isWin()) {
				_state = IN_MENU;
				setScore(highscore);
			}
		}
		_lib->refreshWindow();
		_key = _lib->getKey();
		handleKeys();
	}
	_lib->closeWindow();
}

void N_Console::changeLibs(const Type &type)
{
	if (type == LIBS)
		_lib = _getLib();
	else
		_game = _getGame();
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
	try {
		loopConsole();
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		return Macro::ERROR;
	}
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