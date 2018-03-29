//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// snake
//

#include "Snake.hpp"

void arcade::Snake::setKey(const Key &key)
{
	_key = key;
}

arcade::Snake::Snake()
{
	initMap();
};

void arcade::Snake::initMap()
{
	_x = 1;
	_y = 0;
	_score = 0;

	_map.clear();
	_snakePos.clear();

	_map.push_back("##############################");
	for (auto i = 0 ; i < 30 ; i++)
		_map.push_back("#                            #");
	_map.push_back("##############################");

	_snakePos.push_back({15, 16});
	_snakePos.push_back({15, 15});
	_snakePos.push_back({15, 14});
	_snakePos.push_back({15, 13});
	addApple();
	_pause = false;
}

void arcade::Snake::headSide(std::pair<int, int> const &pos) {
	if (_x == 1)
		_map[pos.first][pos.second] = '1';
	else if (_x == -1)
		_map[pos.first][pos.second] = '2';
	else if (_y == -1)
		_map[pos.first][pos.second] = '3';
	else
		_map[pos.first][pos.second] = '4';
}

void arcade::Snake::bodySide(std::pair<int, int> &prevPos, std::pair<int, int> const &pos) {
	int y = prevPos.first - pos.first;
	int x = prevPos.second - pos.second;

	if (x == 1)
		_map[pos.first][pos.second] = '5';
	else if (x == -1)
		_map[pos.first][pos.second] = '6';
	else if (y == -1)
		_map[pos.first][pos.second] = '7';
	else
		_map[pos.first][pos.second] = '8';
}

void arcade::Snake::fillMap()
{
	std::size_t i = 0;
	std::pair<int, int> prevPos;

	for (auto &pos : _snakePos) {
		if (i == 0)
			headSide(pos);
		else
			bodySide(prevPos, pos);
		i++;
		prevPos = pos;
	}
}

void arcade::Snake::clearMap()
{
	for (auto &pos : _snakePos)
		_map[pos.first][pos.second] = ' ';
}

void arcade::Snake::getNewSide()
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
		case RESET:
			initMap(); break;
		default:
			break;
	}
}

void arcade::Snake::checkCollision(std::pair<std::size_t, std::size_t> &pos)
{
	auto snake = find(_snakePos.begin() + 1, _snakePos.end(), pos);

	if (snake != _snakePos.end())
		initMap();
}

void arcade::Snake::addApple()
{
	std::pair<std::size_t, std::size_t> pos = {rand() % 29 + 1, rand() % 28 + 1};
	auto snake = find(_snakePos.begin(), _snakePos.end(), pos);

	while (snake != _snakePos.end()) {
		pos = {rand() % 30 + 1, rand() % 28 + 1};
		snake = find(_snakePos.begin(), _snakePos.end(), pos);
	}

	_map[pos.first][pos.second] = 'o';
}

bool arcade::Snake::checkApple(std::pair<std::size_t, std::size_t> &pos)
{
	if (_map[pos.first][pos.second] == 'o') {
		_score += 100;
		addApple();
		return false;
	}

	return true;
}

void arcade::Snake::moveSnake()
{
	std::pair<std::size_t, std::size_t> pos;

	pos.first = _snakePos[0].first + _y;
	if (pos.first >= _map.size() - 1)
		pos.first = 1;
	else if (pos.first < 1)
		pos.first = _map.size() - 2;

	pos.second = _snakePos[0].second + _x;
	if (pos.second >= _map.size() - 3)
		pos.second = 1;
	else if (pos.second < 1)
		pos.second = _map.size() - 4;

	_snakePos.insert(_snakePos.begin(), pos);

	checkCollision(pos);
	if (checkApple(pos))
		_snakePos.erase(_snakePos.end());
}

void arcade::Snake::startChrono()
{
	_previousLoop = std::chrono::system_clock::now();
}

bool arcade::Snake::doLoop()
{
	auto period = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - _previousLoop).count();

	if (period < 100)
		return false;

	_previousLoop = std::chrono::system_clock::now();
	return true;
}

int arcade::Snake::start(std::unique_ptr<arcade::IGraphics> &lib)
{
	lib->clearWindow();
	fillMap();
	lib->drawMap(_map);
	clearMap();
	lib->drawText("Score : " + std::to_string(_score), 10, 10, BLUE);
	if (doLoop() && !_pause)
		moveSnake();
	getNewSide();
	lib->refreshWindow();
	return _score;
}

extern "C" std::unique_ptr<arcade::IGame> launch()
{
	return std::make_unique<arcade::Snake>();
}