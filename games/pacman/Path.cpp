/*
** EPITECH PROJECT, 2018
** test
** File description:
** Path
*/

#include "Path.hpp"

Pos &Pos::operator=(const Pos &rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

bool Pos::operator==(const Pos &rhs) const
{
	return x == rhs.x && y == rhs.y;
}

Pos operator+(const Pos &lhs, const Pos &rhs)
{
	return {lhs.x + rhs.x, lhs.y + rhs.y};
}

bool Path::dfs(const Pos &start, const Pos &goal)
{
	Pos tmp;

	if (start == goal)
		return true;
	if (!_visited[start.y][start.x]) {
		_visited[start.y][start.x] = true;
		for (std::size_t i = 0; i < _dirs.size(); i++) {
			tmp = start + _dirs[i];
			if (tmp.x >= 0 and
				tmp.y >= 0 and
				tmp.y < static_cast<int>(_visited.size()) and
				tmp.x < static_cast<int>(_visited[tmp.y].size()) and
				dfs(tmp, goal) == true)
				return _path.push_back(tmp), true;
		}
	}
	return false;
}

std::vector<Pos> Path::findPath(const Pos &start, const Pos &goal)
{
	_visited.resize(_map.size());
	for (std::size_t y = 0; y < _map.size(); y++) {
		for (std::size_t x = 0; x < _map[y].size(); x++) {
			if (_map[y][x] == '#')
				_visited[y].push_back(true);
			else
				_visited[y].push_back(false);
		}
	}
	dfs(start, goal);
	std::reverse(_path.begin(), _path.end());
	if (_path.empty())
		std::cout << "MDR" << std::endl;
	return _path;
}