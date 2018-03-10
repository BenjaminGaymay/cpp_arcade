//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// LibSfml
//

#pragma once

#include <SFML/Graphics.hpp>
#include "IGraphics.hpp"

namespace arcade {
	class LibSfml : public IGraphics {
	public:
		LibSfml();
		~LibSfml();

		void drawText(const std::string &, const int &, const int &, const Color &);
		void drawSquare(const int &, const int &, const Color &);
		void clearWindow();
		void refreshWindow();
		void display(std::vector<std::string> &lol) {};
		void render() {};
		void getKey() {};
		void closeWindow();
		void openWindow();
		int getWidth() {};
		int getHeight() {};

	private:
		int _width;
		int _height;
		sf::RenderWindow _window;
		sf::Font _font;
		sf::Text _text;
	};
}