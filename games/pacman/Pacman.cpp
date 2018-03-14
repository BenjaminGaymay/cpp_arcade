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
	_state = PacmanState::NORMAL;
	_score = 0;

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
	_map.push_back("   BWBWWWWWWWWSBWB   ");
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
	_map.push_back("BWWWWWWWWWSWWWWWWWWWB");
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
	_map[_pacmanPos.first][_pacmanPos.second] = (_state == PacmanState::SUPER ? 'b' : 'Y');

	for (auto &ghost : _ghostPos) {
		switch (ghost->_state) {
			case GhostState::ALIVE:
				_map[ghost->_pos.first][ghost->_pos.second] = '^'; break;
			case GhostState::EATABLE:
				_map[ghost->_pos.first][ghost->_pos.second] = 'v'; break;
			case GhostState::DEAD:
				_map[ghost->_pos.first][ghost->_pos.second] = 'x'; break;
		}
	}
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

void arcade::Pacman::manageSuperMod(std::pair<int, int> &pos)
{
	if (_state == PacmanState::SUPER) {
		auto period = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - _superMod).count();

		if (period > 7500) {
			_state = PacmanState::NORMAL;
			for (auto &ghost : _ghostPos)
				ghost->_state = (ghost->_state == GhostState::EATABLE ? GhostState::ALIVE : ghost->_state);
		}
	}
	if (_map[pos.first][pos.second] == 'S') {
		_state = PacmanState::SUPER;
		for (auto &ghost : _ghostPos)
			ghost->_state = (ghost->_state == GhostState::ALIVE ? GhostState::EATABLE : ghost->_state);
		_superMod = std::chrono::system_clock::now();
	}
}


bool arcade::Pacman::checkGhostCollision()
{
	for (auto &ghost : _ghostPos) {
		if (ghost->_pos == _pacmanPos && ghost->_state == GhostState::EATABLE) {
			ghost->_state = GhostState::DEAD;
			ghost->_deadTime = std::chrono::system_clock::now();
			_score += 5000;
		}
		else if (ghost->_pos == _pacmanPos && ghost->_state == GhostState::ALIVE)
			return initMap(), true;
	}
	return false;
}

void arcade::Pacman::movePacman()
{
	std::pair<int, int> pos;

	if (checkGhostCollision())
		return ;
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

	if (_map[pos.first][pos.second] != 'B' && _map[pos.first][pos.second] != '-') {
		_pacmanPos = pos;
		_score += (_map[pos.first][pos.second] == 'W' ? 100 : 0);
	}

	manageSuperMod(_pacmanPos);
	checkGhostCollision();
}

void arcade::Pacman::moveGhosts()
{
	int period;

	for (auto &ghost : _ghostPos) {
		period = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - ghost->_deadTime).count();
		if (ghost->_state == GhostState::DEAD and period > 5000)
			ghost->_state = GhostState::ALIVE;
		ghost->move(_map);
	}
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
	lib->drawText("Score : " + std::to_string(_score), 30, 10, BLUE);
	for (unsigned i = 0 ; i < _ghostPos.size() ; i++) {
		std::string state;
		switch (_ghostPos[i]->_state) {
			case GhostState::ALIVE:
				state = "Alive"; break;
			case GhostState::EATABLE:
				state = "Eatable"; break;
			case GhostState::DEAD:
				state = "Dead"; break;
		}
		lib->drawText("State : " + state, 10, 10 + i * 2, BLUE);
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
