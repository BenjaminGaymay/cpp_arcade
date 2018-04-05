//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibNcurses
//

#include "LibNcurses.hpp"

using N_LibNcurses = arcade::LibNcurses;

N_LibNcurses::LibNcurses()
{
	srand(time(NULL));
	_keyMatch[27] = ESC;
	_keyMatch[KEY_UP] = UP;
	_keyMatch[KEY_DOWN] = DOWN;
	_keyMatch[KEY_LEFT] = LEFT;
	_keyMatch[KEY_RIGHT] = RIGHT;
	_keyMatch[10] = ENTER;
	_keyMatch['p'] = PAUSE;
	_keyMatch['r'] = RESET;
	_keyMatch['n'] = NEXT_LIB;
	_keyMatch['b'] = PREVIOUS_LIB;
	_keyMatch['m'] = NEXT_GAME;
	_keyMatch['l'] = PREVIOUS_GAME;
	_keyMatch['s'] = SHOOT;
}

N_LibNcurses::~LibNcurses()
{
}

void N_LibNcurses::openWindow()
{
	initscr();
	nodelay(stdscr, TRUE);
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, _height, _width);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_YELLOW, COLOR_BLACK);
	init_pair(9, COLOR_RED, COLOR_RED);
	init_pair(10, COLOR_BLUE, COLOR_BLUE);
	init_pair(11, COLOR_GREEN, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_WHITE);
	init_pair(13, COLOR_BLACK, COLOR_BLACK);
	init_pair(14, COLOR_CYAN, COLOR_CYAN);
	init_pair(15, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(16, COLOR_YELLOW, COLOR_YELLOW);

}

bool N_LibNcurses::isOpen()
{
	return true;
}

void N_LibNcurses::closeWindow()
{
	endwin();
}

void N_LibNcurses::clearWindow()
{
	clear();
}

void N_LibNcurses::refreshWindow()
{
	refresh();
}

void N_LibNcurses::drawText(const std::string &text, const int &x, const int &y, const Color &color)
{
	attron(COLOR_PAIR(color));
	mvprintw(y, x, "%s", text.c_str());
	attroff(COLOR_PAIR(color));
}

arcade::Color N_LibNcurses::setColor(char c)
{
	switch (c) {
		case 'R':
		case 'o':
		case 'h':
			return arcade::BG_RED;
		case 'B':
		case 'g':
		case '#':
			return arcade::BG_BLUE;
		case 'G':
		case '5':
		case '6':
		case '7':
		case '8':
		case 'e':
			return arcade::BG_GREEN;
		case 'W':
		case '.':
			return arcade::BG_WHITE;
		case 'C':
		case 'i':
			return arcade::BG_CYAN;
		case 'M':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'f':
			return arcade::BG_MAGENTA;
		case 'Y':
		case '1':
		case '2':
		case '3':
		case '4':
		case 's':
			return arcade::BG_YELLOW;
		default:
			return arcade::BG_BLACK;
	}
}

void N_LibNcurses::drawMap(const std::vector<std::string> &map)
{
	arcade::Color color;

	for (unsigned i = 0 ; i < map.size() ; i++) {
		for (unsigned j = 0 ; j < (map[i].size() * 2) ; j++) {
			color = setColor(map[i][j / 2]);
			drawSquare(getWidth() / 2 - (map[i].size() - 1) + j, getHeight() / 2 - (map.size() / 2) + i, color);
		}
	}
}

void N_LibNcurses::drawSquare(const int &x, const int &y, const Color &color)
{
	attron(COLOR_PAIR(color));
	mvprintw(y, x, "X");
	attroff(COLOR_PAIR(color));
}

int N_LibNcurses::getHeight()
{
	return _height;
}

int N_LibNcurses::getWidth()
{
	return _width;
}

arcade::Key N_LibNcurses::getKey()
{
	_key = getch();

	if (_keyMatch.find(_key) != _keyMatch.end())
		return _keyMatch[_key];
	else
		return NONE;
}

void N_LibNcurses::drawListLibs(const std::vector<std::string> &libs, int size_width, int size_height, std::size_t _index)
{
	static int loop = 0;
	int i = 0;
	std::size_t j = 0;
	Color color;

	for (auto name : libs) {
		if (_index == j) {
			color = RED;
			for ( auto &c : name)
				c = toupper(c);
			if (loop % 5000 < 2500)
				drawSquare((size_width / 3) + 5, (size_height / 3) + i, arcade::BG_RED);
		}
		else
			color = BLUE;
		name[0] = toupper(name[0]);
		drawText(name, (size_width / 3) + 10, (size_height / 3) + i, color);
		i += 5;
		j++;
	}
	loop++;
}

void N_LibNcurses::drawListGames(const std::vector<std::string> &games, std::size_t size, int size_width, int size_height, std::size_t _index)
{
	static int loop = 0;
	int i = 0;
	std::size_t j = size;
	Color color;

	for (auto name : games) {
		if (_index == j) {
			color = RED;
			for ( auto &c : name)
				c = toupper(c);
			if (loop % 2500 < 1250)
				drawSquare((size_width / 2) + (name.size() + 15), (size_height / 3) + i, arcade::BG_RED);
			printScore(games, size, _index);
		}
		else
			color = BLUE;
		name[0] = toupper(name[0]);
		drawText(name, (size_width / 2) + 10, (size_height / 3) + i, color);
		i += 5;
		j++;
	}
	loop++;
}

std::vector<std::string> N_LibNcurses::splitString(std::string str, char separator)
{
	std::string tmp = "";
	std::vector<std::string> splited;

	for (auto c: str) {
		if (c != separator)
			tmp += c;
		else if (c == separator && tmp != "") {
			splited.push_back(tmp);
			tmp = "";
		}
	}
	if (tmp != "")
		splited.push_back(tmp);
	return splited;
}

void N_LibNcurses::printScore(const std::vector<std::string> &games, std::size_t size, std::size_t _index)
{
	std::string _gameName = games[_index - size];
	int i = 0;

	std::ifstream readScore("scoreboard/" + _gameName + ".score");
	std::string line;
	std::vector<std::string> split;
	std::vector<std::pair<int, std::string>> scoreboard;

	if (!readScore)
		return ;

	while (std::getline(readScore, line) && i < 30) {
		if (!line.empty()) {
			split = std::vector<std::string> (splitString(line, ':'));
			 if (split.size() == 2){
				 drawText(split[0], (getWidth() / 2) + 60, (getHeight() / 4) + i, GREEN);
				 drawText(split[1], (getWidth() / 2) + (split[0].size() + 65), (getHeight() / 4) + i, GREEN);
			 }
		}
		i = i + 3;
	}
	readScore.close();
}

std::string N_LibNcurses::getPseudo()
{
	static std::string line;
	int character;

	character = getch();
	drawText("Your pseudo :", (getWidth() / 3) + 0, (getHeight() / 3) + 10, RED);
  	if (static_cast<char>(character) == '\n' or line.size() >= 12)
		return line;
	if (isalnum(character))
		line = line + static_cast<char>(character);
	else if (character == KEY_BACKSPACE)
		line = line.substr(0, line.size() - 1);
	drawText(line, (getWidth() / 3) + 15, (getHeight() / 3) + 10, RED);
  	return "Bertrand";
}

void N_LibNcurses::drawMenu(const std::vector<std::string> &libs, const std::vector<std::string> &games, std::size_t _index)
{
	static int loop = 0;
	static int x = rand() % 2 - rand() % 1;
	static int y = rand() % 2 -  rand() % 1;
	int color = rand() % 7;

	if (loop % 1000 == 0) {
		x = rand() % 2 - rand() % 1;
		y = rand() % 2 -  rand() % 1;
	}
	color = (color == BLACK ? color + 1 : color);
	drawText("  ___  ______  _____   ___ ______ _____ ", (getWidth() / 3) + 15 + x, (getHeight() / 3) - 10 + y, (arcade::Color)color);
	drawText(" / _ \\ | ___ \\/  __ \\ / _ \\|  _  \\  ___|", (getWidth() / 3) + 15 + x, (getHeight() / 3) - 9 + y, (arcade::Color)color);
	drawText("/ /_\\ \\| |_/ /| /  \\// /_\\ \\ | | | |__  ", (getWidth() / 3) + 15 + x, (getHeight() / 3) - 8 + y, (arcade::Color)color);
	drawText("|  _  ||    / | |    |  _  | | | |  __| ", (getWidth() / 3) + 15 + x, (getHeight() / 3) - 7 + y, (arcade::Color)color);
	drawText("| | | || |\\ \\ | \\__/\\| | | | |/ /| |___ ", (getWidth() / 3) + 15 + x, (getHeight() / 3) - 6 + y, (arcade::Color)color);
	drawText("\\_| |_/\\_| \\_| \\____/\\_| |_/___/ \\____/ ", (getWidth() / 3) + 15 + x, (getHeight() / 3) - 5 + y, (arcade::Color)color);
	drawListLibs(libs, getWidth(), getHeight() + 10, _index);
	drawListGames(games, libs.size(), getWidth() + 20, getHeight() + 10, _index);
	loop++;
}

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibNcurses>();
}