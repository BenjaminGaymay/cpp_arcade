//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// main
//

#include "Console.hpp"
#include "Macro.hpp"

int main(int ac, char **av)
{
	arcade::Console lol;

	if (ac != 2) {
		std::cerr << "Error: program needs a lib to run." << std::endl;
		return Macro::ERROR;
	}
	try {
		lol.loadLibs("./lib/", arcade::Console::LIBS);
		lol.loadLibs("./games/", arcade::Console::GAME);
		lol.setLib(av[1]).openLib();
		lol.showList();
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		return Macro::ERROR;
	}
	return lol.launch();
}