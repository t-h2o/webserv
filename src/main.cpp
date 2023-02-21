#include "arguments.hpp"
#include <iostream>

int
main(int argc, char **argv)
{
	(void)argv;

	if (check_argc_number(argc))
		return 1;

	std::cout << "C++ template" << std::endl;
	return 0;
}
