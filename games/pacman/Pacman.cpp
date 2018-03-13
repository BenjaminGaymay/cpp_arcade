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
	for (unsigned i = 0 ; i < _ghostPos.size() ; i++)
		delete _ghostPos[i];
	_ghostPos.clear();

	_map.push_back("BBBBBBBBBBBBBBBBBBBBB");
	_map.push_back("BWWWWWWWWWBWWWWWWWWWB");
	_map.push_back("BWBBWBBBBWBWBBBBWBBWB");
	_map.push_back("BWWWWWWWWWWWWWWWWWWWB");
	_map.push_back("BWBBWBWBBBBBBBWBWBBWB");
	_map.push_back("BWWWWBWWWWBWWWWBWWWWB");
	_map.push_back("BBBBWBBBBWBWBBBBWBBBB");
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

	_pacmanPos = {7, 10};
	_ghostPos.push_back(new Ghost('-', {9, 12}));
	_ghostPos.push_back(new Ghost('-', {9, 11}));
	_ghostPos.push_back(new Ghost('-', {9, 9}));
	_ghostPos.push_back(new Ghost('-', {9, 8}));
	_pause = false;
}

void arcade::Pacman::fillMap()
{
	_map[_pacmanPos.first][_pacmanPos.second] = 'Y';

	for (auto &ghost : _ghostPos)
		_map[ghost->_pos.first][ghost->_pos.second] = '^';
}

void arcade::Pacman::clearMap()
{
	_map[_pacmanPos.first][_pacmanPos.second] = ' ';

	for (auto &ghost : _ghostPos)
		_map[ghost->_pos.first][ghost->_pos.second] = ghost->_prevChar;
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

	for (auto &ghost : _ghostPos) {
		if (ghost->_pos == _pacmanPos)
			initMap();
	}
}

void arcade::Pacman::moveGhosts()
{
	for (auto &ghost : _ghostPos)
		ghost->move(_map);
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
	for (unsigned i = 0 ; i < _ghostPos.size() ; i++) {
		lib->drawText(std::to_string(_ghostPos[i]->_pos.first) + " " + std::to_string(_ghostPos[i]->_pos.second) + " " + std::to_string(_ghostPos[i]->_y) + " " + std::to_string(_ghostPos[i]->_x), 10, 10 + i, BLUE);
	}
	if (doLoop() && !_pause) {
		moveGhosts();
		movePacman();
	}
	getNewSide();
	lib->refreshWindow();
}

extern "C" std::unique_ptr<arcade::IGame> launch()
{
	return std::make_unique<arcade::Pacman>();
}
