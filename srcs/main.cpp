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
	arcade::Console PS4;

	if (ac != 2)
		return std::cerr << "Error: program needs a lib to run." << std::endl, Macro::ERROR;
	try {
		PS4.setLibName(av[1]);
		PS4.openLib();
		PS4.loadLibs("./lib/", arcade::Console::LIBS);
		PS4.loadLibs("./games/", arcade::Console::GAME);
		PS4.showList();
	} catch (std::runtime_error &e) {
		return std::cerr << e.what() << std::endl, Macro::ERROR;
	}
	return PS4.launch();
}