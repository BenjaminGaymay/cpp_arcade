//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibOpengl
//

#pragma once

#include <memory>
#include <map>
#include <dlfcn.h>
#include <dirent.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
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
		std::string getPseudo();
		std::vector<std::string> splitString(std::string , char );
		void drawMenu(const std::vector<std::string> &, const std::vector<std::string> &, std::size_t);
		void printScore(const std::vector<std::string> &, std::size_t, std::size_t);
		void drawListLibs(const std::vector<std::string> &, int , int , std::size_t );
		void drawListGames(const std::vector<std::string> &, std::size_t, int , int , std::size_t );

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
		sf::Keyboard::Key _key;
		sf::Sprite _bg;
		sf::Texture _bgText;
		sf::Texture _titleImgText;
		sf::Sprite _title;
		sf::Music _music;

		std::map<Color, sf::Color> _colorsMatch;
		std::map<sf::Keyboard::Key, Key> _keyMatch;
		std::map<Color, sf::Texture> _textureMatch;

		std::vector<sf::Texture> _texture;
	};
}