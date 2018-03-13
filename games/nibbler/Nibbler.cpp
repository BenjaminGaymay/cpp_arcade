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
	_map.push_back("WR     R               R     RW");
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

	_nibblerPos.push_back({15, 12});
	_nibblerPos.push_back({15, 11});
	_nibblerPos.push_back({15, 10});
	_nibblerPos.push_back({15, 9});
	_pause = false;
}

void arcade::Nibbler::fillMap()
{
	for (auto &pos : _nibblerPos)
		_map[pos.first][pos.second] = 'G';
}

void arcade::Nibbler::clearMap()
{
	for (auto &pos : _nibblerPos)
		_map[pos.first][pos.second] = ' ';
}

void arcade::Nibbler::getNewSide()
{
	switch (_key) {
		case UP:
			_x = 0; _y = (_y != 1 ? -1 : _y); break;
		case LEFT:
			_y = 0;	_x = (_x != 1 ? -1 : _x); break;
		case DOWN:
			_x = 0; _y = (_y != -1 ? 1 : _y); break;
		case RIGHT:
			_y = 0;	_x = (_x != -1 ? 1 : _x); break;
		case PAUSE:
			_pause = _pause ? false : true; break;
		case ESC:
			initMap(); break;
		default:
			break;
	}
}

void arcade::Nibbler::checkCollision(std::pair<std::size_t, std::size_t> &pos)
{
	auto nibbler = find(_nibblerPos.begin() + 1, _nibblerPos.end(), pos);

	if (_map[pos.first][pos.second] == 'W' or nibbler != _nibblerPos.end())
		initMap();
}

bool arcade::Nibbler::checkApple(std::pair<std::size_t, std::size_t> &pos)
{
	if (_map[pos.first][pos.second] == 'R')
		return false;

	return true;
}

void arcade::Nibbler::moveNibbler()
{
	std::pair<std::size_t, std::size_t> pos;

	pos.first = _nibblerPos[0].first + _y;
	pos.second = _nibblerPos[0].second + _x;

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

	if (period < 150)
		return false;

	_previousLoop = std::chrono::system_clock::now();
	return true;
}

void arcade::Nibbler::start(std::unique_ptr<arcade::IGraphics> &lib)
{
	fillMap();
	lib->drawMap(_map);
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