//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Ghost
//

#include "Ghost.hpp"

arcade::Ghost::Ghost (const char &c, const std::pair<int, int> &pos) :
	_canMove(false), _x(0), _y(0), _prevChar(c),
	_state(GhostState::ALIVE), _pos(pos),
	_lifeTime(std::chrono::system_clock::now()),
	_deadTime(std::chrono::system_clock::now())
{
}

std::pair<int, int> arcade::Ghost::choseSide(std::vector<std::string> &map)
{
	std::vector<std::pair<int, int>> possibilities;

	if (map[_pos.first + 1][_pos.second] != '#')
		possibilities.push_back({1, 0});
	if (map[_pos.first - 1][_pos.second] != '#')
		possibilities.push_back({-1, 0});
	if (map[_pos.first][_pos.second + 1] != '#')
		possibilities.push_back({0, 1});
	if (map[_pos.first][_pos.second - 1] != '#')
		possibilities.push_back({0, -1});

	if (possibilities.size() == 0)
		return {0, 0};
	else if (possibilities.size() == 2 and map[_pos.first + _y][_pos.second + _x] != '#' and !(_y == 0 and _x == 0))
		return {_y, _x};

	auto tmp = possibilities[rand() % possibilities.size()];

	while (tmp.first == _y and tmp.second == _x)
		tmp = possibilities[rand() % possibilities.size()];
	return tmp;
}

bool arcade::Ghost::canMove(std::vector<std::string> &map)
{
	if (_canMove)
		return true;

	auto period = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - _lifeTime).count();

	if (period > rand()  % 60000 + 10000) {
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

void arcade::Ghost::setPacMan(const Pos &pos)
{
	_pacmanPos = pos;
}

void arcade::Ghost::setPacMan(const std::pair<int, int> &pos)
{
	_pacmanPos.y = pos.first;
	_pacmanPos.x = pos.second;
}

void arcade::Ghost::moveAlive(std::vector<std::string> &map, Pos &pos)
{
	std::vector<Pos> nextPos;
	Astar path(map);

	nextPos = path.findPath(pos, _pacmanPos);
	if (nextPos.size() < 2)
		return ;

	std::reverse(nextPos.begin(), nextPos.end());

	_y = nextPos[1].y - _pos.first;
	_x = nextPos[1].x - _pos.second;
	_pos.first = nextPos[1].y;
	_pos.second = nextPos[1].x;
}

void arcade::Ghost::moveEatable(std::vector<std::string> &map)
{
	auto side = choseSide(map);

	_pos.first += side.first;
	_pos.second += side.second;
	_x = side.second;
	_y = side.first;
}

void arcade::Ghost::moveDead(std::vector<std::string> &map, Pos &pos)
{
	std::vector<Pos> nextPos;
	Astar path(map);
	auto house = Pos(10, 9);

	if (pos == house) {
		_state = ALIVE;
		return ;
	}
	nextPos = path.findPath(pos, house);
	if (nextPos.size() < 2)
		return ;

	std::reverse(nextPos.begin(), nextPos.end());

	_y = nextPos[1].y - _pos.first;
	_x = nextPos[1].x - _pos.second;
	_pos.first = nextPos[1].y;
	_pos.second = nextPos[1].x;
}

void arcade::Ghost::move(std::vector<std::string> &map)
{
	Pos pos;
	pos.y = _pos.first;
	pos.x = _pos.second;

	switch (_state) {
		case EATABLE:
			moveEatable(map); break;
		case ALIVE:
			moveAlive(map, pos); break;
		case DEAD:
			moveDead(map, pos); break;
	}
	map[pos.y][pos.x] = _prevChar;


	if (_pos.first >= static_cast<int>(map.size()))
		_pos.first = 0;
	else if (_pos.first == 0)
		_pos.first = map.size() - 1;

	if (_pos.second < 0)
		_pos.second = map[_pos.first].size() - 1;
	else if (_pos.second > static_cast<int>(map[_pos.first].size()) - 1)
		_pos.second = 0;

	_prevChar = map[_pos.first][_pos.second];
}
