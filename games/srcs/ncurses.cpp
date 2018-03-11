//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// snake
//

#include "ncurses.hpp"

void initColor()
{
  init_pair(1, COLOR_RED, COLOR_RED);
  init_pair(2, COLOR_GREEN, COLOR_GREEN);
  init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);
  init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(6, COLOR_CYAN, COLOR_CYAN);
  init_pair(7, COLOR_WHITE, COLOR_WHITE);
  init_pair(8, COLOR_WHITE, COLOR_BLACK);
  init_pair(9, COLOR_RED, COLOR_BLACK);
  init_pair(10, COLOR_GREEN, COLOR_BLACK);
  init_pair(11, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(12, COLOR_CYAN, COLOR_BLACK);
}

void setColor(char c)
{
	switch (c) {
		case '*':
			attron(COLOR_PAIR(7)); break;
		case 'G':
			attron(COLOR_PAIR(2)); break;
		case 'R':
			attron(COLOR_PAIR(1)); break;
		default:
			attron(COLOR_PAIR(8)); break;
	}
}

void showMap(std::vector<std::string> &map)
{
	for (unsigned i = 0 ; i < map.size() ; i++) {
		for (unsigned f = 0 ; f < map.size() * 2 ; f++) {
			move(LINES / 2 - (map.size() / 2) + i, COLS / 2 - map.size() + f);
			setColor(map[i][f / 2]);
			printw("%c", map[i][f / 2]);
		}
	}
}

void initNcurses()
{
	initscr();
	nodelay(stdscr, TRUE);
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	start_color();
	srand(time(NULL));
	initColor();
}