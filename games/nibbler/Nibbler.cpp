//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// nibbler
//

#include "Nibbler.hpp"

void arcade::Nibbler::setKey(const Key &key)
{
	_key = key;
}

arcade::Nibbler::Nibbler()
{
	initMap();
};

void arcade::Nibbler::initMap()
{
	_x = 1;
	_y = 0;

	_map.clear();
	_nibblerPos.clear();
	_applePos.clear();
	_wallPos.clear();

	_map.push_back("WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
	_map.push_back("W  R         R   R         R  W");
	_map.push_back("W WWWWWWWWWWW W W WWWWWWWWWWW W");
	_map.push_back("WR        R   W W   R        RW");
	_map.push_back("W WWWWWWWW WWWW WWWW WWWWWWWW W");
	_map.push_back("W W      W  R     R  W      W W");
	_map.push_back("W W      W WWWWWWWWW W      W W");
	_map.push_back("W W      W     R     W      W W");
	_map.push_back("W W      W WWWWWWWWW W      W W");
	_map.push_back("W W      W  R  W  R  W      W W");
	_map.push_back("W W      WWWWW W WWWWW      W W");
	_map.push_back("W W      W     W     W      W W");
	_map.push_back("W WWWWWWWW WWWWWWWWW WWWWWWWW W");
	_map.push_back("WR     R               R     RW");
	_map.push_back("WWWWW WWWWWWWWWRWWWWWWWWW WWWWW");
	_map.push_back("WR     R GGGG          R     RW");
	_map.push_back("W WWWWWWWWWWWWW WWWWWWWWWWWWW W");
	_map.push_back("W  R          W W          R  W");
	_map.push_back("W WWWWWWWWWWW  R  WWWWWWWWWWW W");
	_map.push_back("W     W     W W W W     W     W");
	_map.push_back("WRW W R WWW R W W R WWW R W WRW");
	_map.push_back("W W WWWWWWWWWWWRWWWWWWWWWWW W W");
	_map.push_back("W  R                       R  W");
	_map.push_back("W WWWWWWWWW W WWW W WWWWWWWWW W");
	_map.push_back("W   W     W W     W W     W  RW");
	_map.push_back("W W R W W R W  W  W R W W R W W");
	_map.push_back("W WWWWW WWWWW WWW WWWWW WWWWW W");
	_map.push_back("W  R          W W          R  W");
	_map.push_back("W WWWWWWWWWWW WWW WWWWWWWWWWW W");
	_map.push_back("WR        R         R        RW");
	_map.push_back("WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");

	for (unsigned line = 0 ; line < _map.size()  ; line++) {
		for (int column = _map[line].size() - 1 ; column >= 0 ; column--) {
			switch (_map[line][column]) {
				case 'R':
					_applePos.push_back({line, column}); _map[line][column] = ' '; break;
				case 'G':
					_nibblerPos.push_back({line, column}); _map[line][column] = ' '; break;
				case 'W':
					_wallPos.push_back({line, column}); _map[line][column] = ' '; break;
			}
		}
	}

	_pause = false;
}

void arcade::Nibbler::fillMap()
{
	for (auto &pos : _applePos)
		_map[pos.first][pos.second] = 'R';

	for (auto &pos : _nibblerPos)
		_map[pos.first][pos.second] = 'G';

	for (auto &pos : _wallPos)
		_map[pos.first][pos.second] = 'W';
}

void arcade::Nibbler::clearMap()
{
	for (auto &pos : _applePos)
		_map[pos.first][pos.second] = ' ';

	for (auto &pos : _nibblerPos)
		_map[pos.first][pos.second] = ' ';
}

// void arcade::Nibbler::addApple()
// {
// 	static auto size = _map.size() - 2;

// 	_applePos.push_back({rand() % size + 1, rand() % (size - 2) + 1});
// }

void arcade::Nibbler::getNewSide()
{
	switch (_key) {
		case UP:
			_x = 0; _y = -1;
			break;
		case LEFT:
			_y = 0;	_x = -1;
			break;
		case DOWN:
			_x = 0; _y = 1;
			break;
		case RIGHT:
			_y = 0;	_x = 1;
			break;
		case PAUSE:
			_pause = _pause ? false : true;
			break;
		case ESC:
			initMap();
			break;
		default:
			break;
	}
}

void arcade::Nibbler::checkCollision(std::pair<std::size_t, std::size_t> &pos)
{
	auto wallCollision = std::find(_wallPos.begin() + 1, _wallPos.end(), pos);
	auto nibblerCollision = std::find(_nibblerPos.begin() + 1, _nibblerPos.end(), pos);

	if (nibblerCollision != _nibblerPos.end() or wallCollision != _wallPos.end())
		initMap();
}

bool arcade::Nibbler::checkApple(std::pair<std::size_t, std::size_t> &pos)
{
	auto apple = std::find(_applePos.begin(), _applePos.end(), pos);

	if (apple != _applePos.end()) {
		_applePos.erase(apple);
		//addApple();
		return false;
	}
	return true;
}

void arcade::Nibbler::moveNibbler()
{
	std::pair<std::size_t, std::size_t> pos;

	pos.first = _nibblerPos[0].first + _y;
	// if (pos.first >= _map.size() - 1)
	// 	pos.first = 1;
	// else if (pos.first < 1)
	// 	pos.first = _map.size() - 2;

	pos.second = _nibblerPos[0].second + _x;
	// if (pos.second >= _map.size() - 3)
	// 	pos.second = 1;
	// else if (pos.second < 1)
	// 	pos.second = _map.size() - 4;

	_nibblerPos.insert(_nibblerPos.begin(), pos);

	checkCollision(pos);
	if (checkApple(pos))
		_nibblerPos.erase(_nibblerPos.end());
}

void arcade::Nibbler::startChrono()
{
	_previousLoop = std::chrono::system_clock::now();
}

bool arcade::Nibbler::doLoop()
{
	auto period = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - _previousLoop).count();

	if (period < 300)
		return false;

	_previousLoop = std::chrono::system_clock::now();
	return true;
}

arcade::Color arcade::Nibbler::setColor(char c)
{
	switch (c) {
		case 'W':
			return arcade::BG_WHITE;
		case 'G':
			return arcade::BG_GREEN;
		case 'R':
			return arcade::BG_RED;
		default:
			return arcade::BG_BLACK;
	}
}

void arcade::Nibbler::showMap(std::unique_ptr<IGraphics> &lib)
{
	arcade::Color color;

	for (unsigned i = 0 ; i < _map.size() ; i++) {
		for (unsigned f = 0 ; f < (_map[i].size() * 2) - 1 ; f++) {
			color = setColor(_map[i][f / 2]);
			lib->drawSquare(COLS / 2 - _map[i].size() + f, LINES / 2 - (_map.size() / 2) + i, color);
		}
	}
}

void arcade::Nibbler::start(std::unique_ptr<arcade::IGraphics> &lib)
{
	lib->clearWindow();
	fillMap();
	showMap(lib);
	clearMap();
	if (doLoop() && !_pause)
		moveNibbler();
	getNewSide();
	lib->refreshWindow();
}

extern "C" std::unique_ptr<arcade::IGame> launch()
{
	return std::make_unique<arcade::Nibbler>();
}