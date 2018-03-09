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
	Arcade::Console lol;

	if (ac != 2) {
		std::cerr << "Error: program needs a lib to run." << std::endl;
		return Macro::ERROR;
	}
	try {
		lol.setLib(av[1]).openLib();
	} catch (std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
	}
	lol.launch();
	// std::cout << lol.getLib() << std::endl;
}