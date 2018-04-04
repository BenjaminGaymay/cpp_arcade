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
	_fps = 24.0f;

	_keyMatch[ALLEGRO_KEY_UP] = UP;
	_keyMatch[ALLEGRO_KEY_DOWN] = DOWN;
	_keyMatch[ALLEGRO_KEY_LEFT] = LEFT;
	_keyMatch[ALLEGRO_KEY_RIGHT] = RIGHT;
	_keyMatch[ALLEGRO_KEY_ENTER] = ENTER;
	_keyMatch[ALLEGRO_KEY_ESCAPE] = ESC;
	_keyMatch[ALLEGRO_KEY_P] = PAUSE;
	_keyMatch[ALLEGRO_KEY_R] = RESET;
	_keyMatch[ALLEGRO_KEY_N] = NEXT_LIB;
	_keyMatch[ALLEGRO_KEY_B] = PREVIOUS_LIB;
	_keyMatch[ALLEGRO_KEY_M] = NEXT_GAME;
	_keyMatch[ALLEGRO_KEY_L] = PREVIOUS_GAME;
	_keyMatch[ALLEGRO_KEY_S] = SHOOT;

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
		!al_init_image_addon() || !al_install_keyboard() ||
		!al_get_monitor_info(0, &info))
		throw std::runtime_error("Error: an error occured while loading the allegro5 library.");
	_eventQueue = al_create_event_queue();
	_timer = al_create_timer(1.0f/_fps);
	al_register_event_source(_eventQueue, al_get_keyboard_event_source());
	al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
	al_start_timer(_timer);
	_width = info.x2 - info.x1;
	_height = info.y2 - info.y1;
	_window = al_create_display(_width, _height);
	if ((_font = al_load_font("./ressources/Lato.ttf", 36, 0)) == nullptr ||
		(_background = al_load_bitmap("./ressources/images/arcade_bg.jpg")) == nullptr)
		throw std::runtime_error("Error: can't load ressources.");
}

void N_LibAllegro::closeWindow()
{
	al_destroy_display(_window);
	al_destroy_font(_font);
	al_destroy_timer(_timer);
	al_destroy_event_queue(_eventQueue);
	al_destroy_bitmap(_background);
}

int N_LibAllegro::getHeight()
{
	return _height;
}

int N_LibAllegro::getWidth()
{
	return _width;
}

int N_LibAllegro::getScaleHeight()
{
	return _height / _sy;
}

int N_LibAllegro::getScaleWidth()
{
	return _width / _sx;
}

void N_LibAllegro::clearWindow()
{
	al_clear_to_color(_colorsMatch[BLACK]);
}

void N_LibAllegro::refreshWindow()
{
	if (_event.timer.source == _timer) {
		al_flip_display();
		// al_draw_bitmap(_background, 0, 0, 0);
	}
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
	al_draw_filled_rectangle(x*_sx, y*_sy, x*_sx+_sx, y*_sy+_sy, _colorsMatch[color]);
}

void N_LibAllegro::drawMap(const std::vector<std::string> &map)
{
	arcade::Color color;

	for (unsigned i = 0 ; i < map.size() ; i++) {
		for (unsigned j = 0 ; j < map[i].size() ; j++) {
			color = setColor(map[i][j]);
			drawSquare(getScaleWidth() / 2 - (map[i].size() / 2 - 1) + j, getScaleHeight() / 2 - (map.size() / 2) + i, color);
		}
	}
}

arcade::Key N_LibAllegro::getKey()
{
	al_wait_for_event(_eventQueue, &_event);
	if (_event.type == ALLEGRO_EVENT_KEY_DOWN)
		return _keyMatch[_event.keyboard.keycode];
	return NONE;
}

arcade::Color N_LibAllegro::setColor(char c)
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

extern "C" std::unique_ptr<arcade::IGraphics> launch()
{
	return std::make_unique<arcade::LibAllegro>();
}
