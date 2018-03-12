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
	_map.push_back("******************************");
	for (auto i = 0 ; i < 30 ; i++)
		_map.push_back("*                            *");
	_map.push_back("******************************");
	_nibblerPos.push_back({10, 9});
	_nibblerPos.push_back({10, 8});
	addApple();
	_pause = false;
}

void arcade::Nibbler::fillMap()
{
	for (auto &pos : _applePos)
		_map[pos.first][pos.second] = 'R';

	for (auto &pos : _nibblerPos)
		_map[pos.first][pos.second] = 'G';
}

void arcade::Nibbler::clearMap()
{
	for (auto &pos : _applePos)
		_map[pos.first][pos.second] = ' ';

	for (auto &pos : _nibblerPos)
		_map[pos.first][pos.second] = ' ';
}

void arcade::Nibbler::addApple()
{
	static auto size = _map.size() - 2;

	_applePos.push_back({rand() % size + 1, rand() % (size - 2) + 1});
}

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
	auto collision = std::find(_nibblerPos.begin() + 1, _nibblerPos.end(), pos);

	if (collision != _nibblerPos.end()) {
		for (auto i = _nibblerPos.size() - 1 ; i > 2 ; i--)
			_nibblerPos.erase(_nibblerPos.begin() + i);
	}
}

bool arcade::Nibbler::checkApple(std::pair<std::size_t, std::size_t> &pos)
{
	auto apple = std::find(_applePos.begin(), _applePos.end(), pos);

	if (apple != _applePos.end()) {
		_applePos.erase(apple);
		addApple();
		return false;
	}
	return true;
}

void arcade::Nibbler::moveNibbler()
{
	std::pair<std::size_t, std::size_t> pos;

	pos.first = _nibblerPos[0].first + _y;
	if (pos.first >= _map.size() - 1)
		pos.first = 1;
	else if (pos.first < 1)
		pos.first = _map.size() - 2;

	pos.second = _nibblerPos[0].second + _x;
	if (pos.second >= _map.size() - 3)
		pos.second = 1;
	else if (pos.second < 1)
		pos.second = _map.size() - 4;

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

	if (period < 100)
		return false;

	_previousLoop = std::chrono::system_clock::now();
	return true;
}

arcade::Color arcade::Nibbler::setColor(char c)
{
	switch (c) {
		case '*':
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
		for (unsigned f = 0 ; f < _map.size() * 2 ; f++) {
			color = setColor(_map[i][f/2]);
			lib->drawSquare(COLS/2-_map.size()+f, LINES/2-(_map.size()/2)+i, color);
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