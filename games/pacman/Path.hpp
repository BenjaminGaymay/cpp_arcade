/*
** EPITECH PROJECT, 2018
** test
** File description:
** Path
*/

#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <list>

using MapStr = std::vector<std::string>;
using MapBool = std::vector<std::vector<bool>>;

struct Pos {
	int x;
	int y;
	Pos &operator=(const Pos &);
	bool operator==(const Pos &) const;
};

Pos operator+(const Pos &, const Pos &);

class Path {
public:
	Path(const MapStr &map) : _map(map)
	{
		_dirs.push_back({-1, 0});
		_dirs.push_back({0, -1});
		_dirs.push_back({1, 0});
		_dirs.push_back({0, 1});
	}
	std::vector<Pos> findPath(const Pos &start_, const Pos &goal_);
	bool dfs(const Pos &, const Pos &);

private:
	MapStr _map;
	MapBool _visited;
	std::vector<Pos> _path;
	std::vector<Pos> _dirs;
	std::size_t rows;
	std::size_t cols;
};