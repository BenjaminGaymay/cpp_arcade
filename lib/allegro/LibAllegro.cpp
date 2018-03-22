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
	_sx = 24;
	_sy = _sx;
	_keyMatch[ALLEGRO_KEY_UP] = UP;
	_keyMatch[ALLEGRO_KEY_DOWN] = DOWN;
	_keyMatch[ALLEGRO_KEY_LEFT] = LEFT;
	_keyMatch[ALLEGRO_KEY_RIGHT] = RIGHT;
	_keyMatch[ALLEGRO_KEY_ENTER] = ENTER;
	_keyMatch[ALLEGRO_KEY_ESCAPE] = ESC;
	_keyMatch[ALLEGRO_KEY_P] = PAUSE;
	_keyMatch[ALLEGRO_KEY_R] = RESET;

	_colorsMatch[RED] = {255, 0, 0, 0};
	_colorsMatch[BG_RED] = {255, 0, 0, 0};
	_colorsMatch[BLUE] = {0, 0, 255, 0};
	_colorsMatch[BG_BLUE] = {0, 0, 255, 0};
	_colorsMatch[GREEN] = {0, 255, 0, 0};
	_colorsMatch[BG_GREEN] = {0, 255, 0, 0};
	_colorsMatch[WHITE] = {255, 255, 255, 0};
	_colorsMatch[BG_WHITE] = {255, 255, 255, 0};
	_colorsMatch[CYAN] = {0, 255, 255, 0};
	_colorsMatch[BG_CYAN] = {0, 255, 255, 0};
	_colorsMatch[MAGENTA] = {255, 0, 255, 0};
	_colorsMatch[BG_MAGENTA] = {255, 0, 255, 0};
	_colorsMatch[YELLOW] = {255, 255, 0, 0};
	_colorsMatch[BG_YELLOW] = {255, 255, 0, 0};
	_colorsMatch[BLACK] = {0, 0, 0, 0};
	_colorsMatch[BG_BLACK] = {0, 0, 0, 0};
}

N_LibAllegro::LibAllegro::~LibAllegro()
{}

void N_LibAllegro::openWindow()
{
	ALLEGRO_MONITOR_INFO info;

	if (!al_init() || !al_init_primitives_addon() ||
		!al_init_font_addon() || !al_init_ttf_addon() ||
		!al_install_keyboard() || !al_get_monitor_info(0, &info))
		throw std::runtime_error("Error: an error occured while loading the allegro5 library.");
	_eventQueue = al_create_event_queue();
	//al_register_event_source(_eventQueue, al_get_display_event_source(_window));
	al_register_event_source(_eventQueue, al_get_keyboard_event_source());
	_width = info.x2 - info.x1;
	_height = info.y2 - info.y1;
	std::cout << _width << "\n" << _height << std::endl;
	_window = al_create_display(_width, _height);
	if ((_font = al_load_font("./ressources/Lato.ttf", 36, 0)) == nullptr)
		throw std::runtime_error("Error: can't load font");
}

void N_LibAllegro::closeWindow()
{
	al_destroy_display(_window);
	al_destroy_font(_font);
}

int N_LibAllegro::getHeight()
{
	return _height / _sy;
}

int N_LibAllegro::getWidth()
{
	return _width / _sx;
}

void N_LibAllegro::clearWindow()
{
	al_clear_to_color(_colorsMatch[BLACK]);
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
	al_draw_text(_font, _colorsMatch[color], x*_sx, y*_sy, ALLEGRO_ALIGN_CENTER, text.c_str());
}

void N_LibAllegro::drawSquare(const int &x, const int &y, const Color &color)
{
	al_draw_rectangle(x*_sx, y*_sy, x*_sx+_sx, y*_sy+_sy, _colorsMatch[color], 1);
}

void N_LibAllegro::drawMap(const std::vector<std::string> &map)
{
	arcade::Color color;

	for (unsigned i = 0 ; i < map.size() ; i++) {
		for (unsigned j = 0 ; j < map[i].size() ; j++) {
			color = setColor(map[i][j]);
			// if (i + 1 < map.size() and color == arcade::BRICK and setColor(map[i + 1][j]) == arcade::BRICK)
			// 	color = arcade::BRICK_HEAD;
			drawSquare(getWidth() / 2 - (map[i].size() / 2 - 1) + j, getHeight() / 2 - (map.size() / 2) + i, color);
		}
	}
}

arcade::Key N_LibAllegro::getKey()
{
	ALLEGRO_EVENT events;

	al_get_next_event(_eventQueue, &events);
	if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		return _keyMatch[events.keyboard.keycode];
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