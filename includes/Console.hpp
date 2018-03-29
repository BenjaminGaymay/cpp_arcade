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
#include "ManageStrings.hpp"

namespace arcade {
	class Console {
	public:
		enum Type {
			GAME,
			LIBS
		};

		enum State {
			IN_MENU,
			IN_GAME
		};

	public:
		Console(const std::string &);
		Console();
		~Console();
		void openLib(const Type &);
		void loadLibs(const std::string &, Type);
		void setLibName(const std::string &);
		void setGameName(const std::string &);
		const std::string &getLibName() const;
		const std::string &getGameName() const;
		std::string epureName(const std::string &);
		void drawListGames();
		void drawListLibs();
		void enterAction();
		void upAction();
		void downAction();
		int writeMenu();
		int launch();
		void drawBox();
		void showList();
		void loopConsole();
		void changeLibs(const Type &);
		void setHighScore(const std::size_t &);
		void setScore(const int);

	private:
		void *_handle;

		std::string _libName;
		std::string _gameName;

		std::unique_ptr<IGraphics> (*_getLib)();
		std::unique_ptr<IGraphics> _lib;
		std::unique_ptr<IGame> (*_getGame)();
		std::unique_ptr<IGame> _game;

		std::vector<std::string> _listLibs;
		std::vector<std::string> _listGames;

		std::size_t _currLib;
		std::size_t _currGame;
		std::size_t _index;

		State _state;
		Key _key;
	};
}