//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Console
//

#pragma once

#include <memory>
#include <iostream>
#include <dlfcn.h>
#include <dirent.h>
#include "IGraphics.hpp"
#include "IGame.hpp"
#include "Macro.hpp"

namespace arcade {
	class Console {
	public:
		enum Type {
			GAME,
			LIBS
		};

	public:
		Console(const std::string &);
		Console();
		~Console();
		void openLib();
		void loadLibs(const std::string &, Type);
		void setLibName(const char *);
		const std::string &getLibName() const;
		int launch();
		void writeMenu();
		void drawBox();
		void drawListLibs();
		void drawListGames();
		void showList();

	private:
		std::string _libName;
		void *_handle;
		std::unique_ptr<IGraphics> (*create)();
		std::unique_ptr<IGraphics> _lib;
		std::vector<std::string> _listLibs;
		std::vector<std::string> _listGames;
		std::size_t _currLib;
		std::size_t _currGame;
	};
}