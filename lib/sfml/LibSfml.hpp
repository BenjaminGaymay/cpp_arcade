//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibSfml
//

#pragma once

#include <memory>
#include <map>
#include <dlfcn.h>
#include <dirent.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "IGraphics.hpp"

namespace arcade {
	class LibSfml : public IGraphics {
	public:
		LibSfml();
		~LibSfml();

		void drawText(const std::string &, const int &, const int &, const Color &);
		void drawSquare(const int &, const int &, const Color &);
		void drawMap(const std::vector<std::string> &map);
		arcade::Color setColor(char c);
		void clearWindow();
		void refreshWindow();
		void render() {};
		Key getKey();
		void closeWindow();
		void openWindow();
		int getWidth();
		int getHeight();
		int getScaleWidth();
		int getScaleHeight();
		bool isOpen();
		std::vector<std::string> splitString(std::string , char );
		void printScore(const std::vector<std::string> &, std::size_t, std::size_t);
		void drawListLibs(const std::vector<std::string> &, int , int , std::size_t );
		void drawListGames(const std::vector<std::string> &, std::size_t, int , int , std::size_t );
		void loadTexture(const std::string &);
		void drawMenu(const std::vector<std::string> &, const std::vector<std::string> &, std::size_t);

	private:
		int _width;
		int _height;
		int _sx;
		int _sy;

		sf::Keyboard::Key _key;
		sf::RenderWindow _window;
		sf::Font _font;
		sf::Text _text;
		sf::Event _event;
		sf::Sprite _bg;

		std::map<Color, sf::Color> _colorsMatch;
		std::map<sf::Keyboard::Key, Key> _keyMatch;
		std::map<Color, sf::Texture> _textureMatch;

		std::vector<sf::Texture> _texture;
	};
}