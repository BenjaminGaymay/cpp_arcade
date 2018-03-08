//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// main
//

#include <exception>
#include <iostream>

class LibException : std::exception {
public:
	LibException(const std::string  &msg):
		_msg(msg) {};
	std::string what()
	{
		return "Error: Lib: " + _msg;
	};
private:
	std::string _msg;
};

void launch(const char *lib)
{
	std::string mdr;

	if (lib == nullptr)
		throw LibException("Bad library file.");
	mdr = lib;
	std::cout << mdr << std::endl;
}

void displayHelp()
{
	std::cout << "USAGE:\n\t./arcade [lib]\nDESCRIPTION:\n\tlib\tlibrary that contains the game askip" << std::endl;
}

int main(int ac, char **av)
{
	if (ac != 2)
		return displayHelp(), 84;
	try {
		launch(av[1]);
	}
	catch (LibException &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}