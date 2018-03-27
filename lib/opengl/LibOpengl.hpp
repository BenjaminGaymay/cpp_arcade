//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibOpengl
//

#pragma once

#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include "IGraphics.hpp"

namespace arcade {
	class LibOpengl : public IGraphics {
	public:
		LibOpengl();
		~LibOpengl();

		void drawText(const std::string &, const int &, const int &, const Color &);
		void drawSquare(const int &, const int &, const Color &);
		void drawCube(float, float, const GLfloat, const std::vector<int> &);
		void drawMap(const std::vector<std::string> &map);
		Color setColor(char);
		std::vector<int> getColor(const Color &);
		void clearWindow();
		void refreshWindow();
		void render() {};
		Key getKey();
		void closeWindow();
		void openWindow();
		int getWidth();
		int getHeight();
		bool isOpen();

	private:
		unsigned int _mapHeight;
		unsigned int _mapWidth;
		int _width;
		int _height;
		int _sx;
		int _sy;

		sf::RenderWindow _window;
		sf::Font _font;
		sf::Text _text;
		sf::Event _event;

		std::map<Color, sf::Color> _colorsMatch;
		std::map<sf::Keyboard::Key, Key> _keyMatch;
		std::map<Color, sf::Texture> _textureMatch;

		std::vector<sf::Texture> _texture;
	};
}