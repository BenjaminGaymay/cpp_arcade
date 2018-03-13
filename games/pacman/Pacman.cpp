//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// pacman
//

#include "Pacman.hpp"

void arcade::Pacman::setKey(const Key &key)
{
	_key = key;
}

arcade::Pacman::Pacman()
{
	initMap();
};

void arcade::Pacman::initMap()
{
	_x = 1;
	_y = 0;

	_map.clear();
	_map.push_back("BBBBBBBBBBBBBBBBBBBBB");
	_map.push_back("BWWWWWWWWWBWWWWWWWWWB");
	_map.push_back("BWBBWBBBBWBWBBBBWBBWB");
	_map.push_back("BWWWWWWWWWWWWWWWWWWWB");
	_map.push_back("BWBBWBWBBBBBBBWBWBBWB");
	_map.push_back("BWWWWBWWWWBWWWWBWWWWB");
	_map.push_back("BBBBWBBBBWWWBBBBWBBBB");
	_map.push_back("   BWBWWWWWWWWWBWB   ");
	_map.push_back("BBBBWBWBBB-BBBWBWBBBB");
	_map.push_back("WWWWWWWB-----BWWWWWWW");
	_map.push_back("BBBBWBWBBBBBBBWBWBBBB");
	_map.push_back("   BWBWWWWWWWWWBWB   ");
	_map.push_back("BBBBWBWBBBBBBBWBWBBBB");
	_map.push_back("BWWWWWWWWWBWWWWWWWWWB");
	_map.push_back("BWBBBWBBBWBWBBBWBBBWB");
	_map.push_back("BWWBWWWWWWWWWWWWWBWWB");
	_map.push_back("BBWBWBWBBBBBBBWBWBWBB");
	_map.push_back("BWWWWBWWWWBWWWWBWWWWB");
	_map.push_back("BWBBBBBBBWBWBBBBBBBWB");
	_map.push_back("BWWWWWWWWWWWWWWWWWWWB");
	_map.push_back("BBBBBBBBBBBBBBBBBBBBB");

	_pacmanPos = {6, 10};
	_pause = false;
}

void arcade::Pacman::fillMap()
{
	_map[_pacmanPos.first][_pacmanPos.second] = 'Y';
}

void arcade::Pacman::clearMap()
{
	_map[_pacmanPos.first][_pacmanPos.second] = ' ';
}

void arcade::Pacman::getNewSide()
{
	switch (_key) {
		case UP:
			_x = 0; _y = -1; break;
		case LEFT:
			_y = 0;	_x = -1; break;
		case DOWN:
			_x = 0; _y = 1; break;
		case RIGHT:
			_y = 0;	_x = 1; break;
		case PAUSE:
			_pause = _pause ? false : true; break;
		case ESC:
			initMap(); break;
		default:
			break;
	}
}

void arcade::Pacman::movePacman()
{
	std::pair<int, int> pos;

	pos.first = _pacmanPos.first + _y;
	if (pos.first >= static_cast<int>(_map.size()))
		pos.first = 0;
	else if (pos.first == 0)
		pos.first = _map.size() - 1;

	pos.second = _pacmanPos.second + _x;
	if (pos.second < 0)
		pos.second = _map[pos.first].size() - 1;
	else if (pos.second > static_cast<int>(_map[pos.first].size()) - 1)
		pos.second = 0;

	if (_map[pos.first][pos.second] != 'B' && _map[pos.first][pos.second] != '-')
		_pacmanPos = pos;
}

void arcade::Pacman::startChrono()
{
	_previousLoop = std::chrono::system_clock::now();
}

bool arcade::Pacman::doLoop()
{
	auto period = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - _previousLoop).count();

	if (period < 200)
		return false;

	_previousLoop = std::chrono::system_clock::now();
	return true;
}

void arcade::Pacman::start(std::unique_ptr<arcade::IGraphics> &lib)
{
	lib->clearWindow();
	fillMap();
	lib->drawMap(_map);
	clearMap();
	if (doLoop() && !_pause)
		movePacman();
	getNewSide();
	lib->refreshWindow();
}

extern "C" std::unique_ptr<arcade::IGame> launch()
{
	return std::make_unique<arcade::Pacman>();
}
