/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** LibAllegro
*/

#include "LibAllegro.hpp"

using N_LibAllegro = arcade::LibAllegro;

N_LibAllegro::LibAllegro::LibAllegro()
{
	_sx = 30;
	_sy = _sx;
}

N_LibAllegro::LibAllegro::~LibAllegro()
{}

void N_LibAllegro::openWindow()
{
	al_init();
	al_get_display_mode(al_get_num_display_modes() - 1, &_disp);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	_window = al_create_display(_disp.width, _disp.height);
	_font = al_load_font("./ressources/Lato.ttf", 15, 0);
}

void N_LibAllegro::closeWindow()
{
	al_destroy_display(_window);
	al_destroy_font(_font);
}

int N_LibAllegro::getHeight()
{
	return _height;
}

int N_LibAllegro::getWidth()
{
	return _width;
}

void N_LibAllegro::clearWindow()
{
	return;
}

void N_LibAllegro::refreshWindow()
{
	al_flip_display();
}

bool N_LibAllegro::isOpen()
{
	return true;
}

void N_LibAllegro::drawText(const std::string &text, const int &x, const int &y, const Color &color)
{
	al_draw_text(_font, al_map_rgb(0,0,0), x*_sx, y*_sy, ALLEGRO_ALIGN_CENTER, text.c_str());
}

void N_LibAllegro::drawSquare(const int &x, const int &y, const Color &color)
{
	al_draw_rectangle(x*_sx, y*_sy, (x+_sx)*_sx, (y+_sy)*_sy, al_map_rgb(12,12,12), 1);
}

void N_LibAllegro::drawMap(const std::vector<std::string> &map)
{
	arcade::Color color;

	for (unsigned i = 0; i < map.size(); i++) {
		for (unsigned j = 0; j < map[i].size(); j++) {
			color = setColor(map[i][j]);
			drawSquare(getWidth() / 2 - (map[i].size() / 2 - 1) + j, getHeight() / 2 - (map.size() / 2) + i, color);
		}
	}
}

arcade::Key N_LibAllegro::getKey()
{
	return NONE;
}

arcade::Color N_LibAllegro::setColor(char c)
{
	switch (c) {
		case 'R':
			return arcade::BG_RED;
		case 'B':
			return arcade::BG_BLUE;
		case 'G':
			return arcade::BG_GREEN;
		case 'W':
			return arcade::BG_WHITE;
		case 'C':
			return arcade::BG_CYAN;
		case 'M':
			return arcade::BG_MAGENTA;
		case 'Y':
			return arcade::BG_YELLOW;
		case '#':
			return arcade::BG_BLUE;
		case 'o':
			return arcade::BG_RED;
		case '.':
			return arcade::BG_WHITE;
		case '1':
			return arcade::BG_BLUE;
		case '2':
			return arcade::BG_BLUE;
		case '3':
			return arcade::BG_BLUE;
		case '4':
			return arcade::BG_BLUE;
		case '5':
			return arcade::BG_CYAN;
		case '6':
			return arcade::BG_CYAN;
		case '7':
			return arcade::BG_CYAN;
		case '8':
			return arcade::BG_CYAN;
		default:
			return arcade::BG_BLACK;
	}
}

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibAllegro>();
}