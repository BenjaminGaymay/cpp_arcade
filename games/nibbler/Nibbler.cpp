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
	_score = 0;

	 _map.push_back("###############################");
	_map.push_back("#  o         o   o         o  #");
	_map.push_back("# ########### # # ########### #");
	_map.push_back("#o        o   # #   o        o#");
	_map.push_back("# ######## #### #### ######## #");
	_map.push_back("# #      #  o     o  #      # #");
	_map.push_back("# #      # ######### #      # #");
	_map.push_back("# #      #     o     #      # #");
	_map.push_back("# #      # ######### #      # #");
	_map.push_back("# #      #  o  #  o  #      # #");
	_map.push_back("# #      ##### # #####      # #");
	_map.push_back("# #      #     #     #      # #");
	_map.push_back("# ######## ######### ######## #");
	_map.push_back("#o     o               o     o#");
	_map.push_back("##### #########o######### #####");
	_map.push_back("#o     o               o     o#");
	_map.push_back("# ############# ############# #");
	_map.push_back("#  o          # #          o  #");
	_map.push_back("# ###########  o  ########### #");
	_map.push_back("#     #     # # # #     #     #");
	_map.push_back("#o# # o ### o # # o ### o # #o#");
	_map.push_back("# # ###########o########### # #");
	_map.push_back("#  o                       o  #");
	_map.push_back("# ######### # ### # ######### #");
	_map.push_back("#   #     # #     # #     #  o#");
	_map.push_back("# # o # # o #  #  # o # # o # #");
	_map.push_back("# ##### ##### ### ##### ##### #");
	_map.push_back("#  o          # #          o  #");
	_map.push_back("# ########### ### ########### #");
	_map.push_back("#o        o         o        o#");
	_map.push_back("###############################");

	_nibblerPos.push_back({15, 12});
	_nibblerPos.push_back({15, 11});
	_nibblerPos.push_back({15, 10});
	_nibblerPos.push_back({15, 9});
	_pause = false;
}

void arcade::Nibbler::headSide(std::pair<int, int> const &pos) {
	if (_x == 1)
		_map[pos.first][pos.second] = '1';
	else if (_x == -1)
		_map[pos.first][pos.second] = '2';
	else if (_y == -1)
		_map[pos.first][pos.second] = '3';
	else
		_map[pos.first][pos.second] = '4';
}

void arcade::Nibbler::bodySide(std::pair<int, int> &prevPos, std::pair<int, int> const &pos) {
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

void arcade::Nibbler::fillMap()
{
	std::size_t i = 0;
	std::pair<int, int> prevPos;

	for (auto &pos : _nibblerPos) {
		if (i == 0)
			headSide(pos);
		else
			bodySide(prevPos, pos);
		i++;
		prevPos = pos;
	}
}

void arcade::Nibbler::clearMap()
{
	for (auto &pos : _nibblerPos)
		_map[pos.first][pos.second] = ' ';
}

void arcade::Nibbler::getNewSide()
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
		case RESET:
		case ESC:
			initMap(); break;
		default:
			break;
	}
}

void arcade::Nibbler::checkCollision(std::pair<std::size_t, std::size_t> &pos)
{
	auto nibbler = find(_nibblerPos.begin() + 1, _nibblerPos.end(), pos);

	if (_map[pos.first][pos.second] == '#' or nibbler != _nibblerPos.end())
		initMap();
}

bool arcade::Nibbler::checkApple(std::pair<std::size_t, std::size_t> &pos)
{
	if (_map[pos.first][pos.second] == 'o')
		return false;

	return true;
}

void arcade::Nibbler::moveNibbler()
{
	std::pair<std::size_t, std::size_t> pos;

	pos.first = _nibblerPos[0].first + _y;
	pos.second = _nibblerPos[0].second + _x;

	_nibblerPos.insert(_nibblerPos.begin(), pos);

	checkCollision(pos);
	if (checkApple(pos))
		_nibblerPos.erase(_nibblerPos.end());
	else
		_score += 250;
}

void arcade::Nibbler::startChrono()
{
	_previousLoop = std::chrono::system_clock::now();
}

bool arcade::Nibbler::doLoop()
{
	auto period = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - _previousLoop).count();

	if (period < 150)
		return false;

	_previousLoop = std::chrono::system_clock::now();
	return true;
}

bool arcade::Nibbler::isWin()
{
	unsigned gum = 0;

	for (unsigned y = 0 ; y < _map.size() ; y++) {
		for (unsigned x = 0 ; x < _map[y].size() ; x++) {
			if (_map[y][x] == 'o')
				gum++;
		}
	}
	return (gum == 0);
}

int arcade::Nibbler::start(std::unique_ptr<arcade::IGraphics> &lib)
{
	fillMap();
	lib->drawMap(_map);
	clearMap();
	lib->drawText("Score : " + std::to_string(_score), 10, 10, BLUE);
	if (doLoop() && !_pause)
		moveNibbler();
	getNewSide();
	lib->refreshWindow();
	return _score;
}

extern "C" std::unique_ptr<arcade::IGame> launch()
{
	return std::make_unique<arcade::Nibbler>();
}