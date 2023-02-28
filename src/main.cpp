#include "Config.hpp"
#include "arguments.hpp"
#include <iostream>

int
main(int argc, char **argv)
{
	(void)argv;

	if (check_argc_number(argc))
		return 1;

	std::cout << "Web server C++98" << std::endl;

	Config config;
	config.insert_pair(std::make_pair("key", new Value("value")));
	config.print_all();
	return 0;
}
