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

int main(int ac, char **av)
{
	try {
		launch(av[1]);
	}
	catch (LibException &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}