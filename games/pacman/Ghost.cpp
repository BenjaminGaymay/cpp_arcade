//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Ghost
//

#include "Ghost.hpp"

std::pair<int, int> arcade::Ghost::choseSide(std::vector<std::string> map)
{
	std::vector<std::pair<int, int>> possibilities;

	if (map[_pos.first + 1][_pos.second] != 'B')
		possibilities.push_back({1, 0});
	if (map[_pos.first - 1][_pos.second] != 'B')
		possibilities.push_back({-1, 0});
	if (map[_pos.first][_pos.second + 1] != 'B')
		possibilities.push_back({0, 1});
	if (map[_pos.first][_pos.second - 1] != 'B')
		possibilities.push_back({0, -1});

	if (possibilities.size() == 0)
		return {0, 0};
	else if (possibilities.size() == 2 and map[_pos.first + _y][_pos.second + _x] != 'B' and !(_y == 0 and _x == 0))
		return {_y, _x};

	auto tmp = possibilities[rand() % possibilities.size()];

	while (tmp.first == _y and tmp.second == _x)
		tmp = possibilities[rand() % possibilities.size()];
	return tmp;
}

bool arcade::Ghost::canMove(std::vector<std::string> map)
{
	if (_canMove)
		return true;

	auto period = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - _lifeTime).count();

	if (period > rand()  % 10000) {
		_canMove = true;
		auto side = choseSide(map);

		_y = side.first;
		_x = side.second;

		_pos.first += _y;
		if (_pos.first >= static_cast<int>(map.size()))
			_pos.first = 0;
		else if (_pos.first == 0)
			_pos.first = map.size() - 1;

		_pos.second += _x;
		if (_pos.second < 0)
			_pos.second = map[_pos.first].size() - 1;
		else if (_pos.second > static_cast<int>(map[_pos.first].size()) - 1)
			_pos.second = 0;

		_prevChar = map[_pos.first][_pos.second];
	}
	return false;
}


void arcade::Ghost::move(std::vector<std::string> map)
{
	if (canMove(map) == false)
		return ;

	map[_pos.first][_pos.second] = _prevChar;

	auto side = choseSide(map);

	_y = side.first;
	_x = side.second;

	if (_pos.first == 9 and _pos.second == 10) {
		_y = -1;
		_x = 0;
	}

	_pos.first += _y;
	if (_pos.first >= static_cast<int>(map.size()))
		_pos.first = 0;
	else if (_pos.first == 0)
		_pos.first = map.size() - 1;

	_pos.second += _x;
	if (_pos.second < 0)
		_pos.second = map[_pos.first].size() - 1;
	else if (_pos.second > static_cast<int>(map[_pos.first].size()) - 1)
		_pos.second = 0;

	_prevChar = map[_pos.first][_pos.second];
}