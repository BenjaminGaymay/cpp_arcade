//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// snake
//

#include "Snake.hpp"

void arcade::Snake::initMap()
{
	_map.push_back("******************************");
	for (auto i = 0 ; i < 30 ; i++)
		_map.push_back("*                            *");
	_map.push_back("******************************");

	_snakePos.push_back({10, 9});
	_snakePos.push_back({10, 8});

	addApple();
}

void arcade::Snake::fillMap()
{
	for (auto &pos : _applePos)
		_map[pos.first][pos.second] = 'R';

	for (auto &pos : _snakePos)
		_map[pos.first][pos.second] = 'G';
}

void arcade::Snake::clearMap()
{
	for (auto &pos : _applePos)
		_map[pos.first][pos.second] = ' ';

	for (auto &pos : _snakePos)
		_map[pos.first][pos.second] = ' ';
}

void arcade::Snake::addApple()
{
	static auto size = _map.size() - 2;

	_applePos.push_back({rand() % size + 1, rand() % (size - 2) + 1});
}


void arcade::Snake::getNewSide()
{
	char key = getch();

	switch (key) {
		case 'z':
			_x = 0; _y = -1; return ;
		case 'q':
			_y = 0;	_x = -1; return ;
		case 's':
			_x = 0; _y = 1;	return ;
		case 'd':
			_y = 0;	_x = 1;	return ;
	}
}

void arcade::Snake::checkCollision(std::pair<std::size_t, std::size_t> &pos)
{
	auto collision = std::find(_snakePos.begin() + 1, _snakePos.end(), pos);

	if (collision != _snakePos.end()) {
		for (auto i = _snakePos.size() - 1 ; i > 2 ; i--)
			_snakePos.erase(_snakePos.begin() + i);
	}
}

bool arcade::Snake::checkApple(std::pair<std::size_t, std::size_t> &pos)
{
	auto apple = std::find(_applePos.begin(), _applePos.end(), pos);

	if (apple != _applePos.end()) {
		_applePos.erase(apple);
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

int main()
{
	arcade::Snake app;

	initNcurses(); //NCURSES

	app.initMap();
	while (true) {
		clear(); //NCURSES
		app.fillMap();
		showMap(app.getMap()); //NCURSES
		app.clearMap();
		app.getNewSide();
		if (app.doLoop() == true)
			app.moveSnake();
		refresh(); //NCURSES
	}
	return 0;
}