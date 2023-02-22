#include <iostream>

#include "arguments.hpp"
#include "webserver.hpp"

int
main(int argc, char **argv)
{
	(void)argv;

	if (check_argc_number(argc))
		return 1;

	std::cout << "Web server written in C++98" << std::endl;
	webserver(argv[1]);

	return 0;
}
