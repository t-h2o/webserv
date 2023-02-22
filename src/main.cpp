#include <iostream>

#include "Config.hpp"
#include "Json.hpp"
#include "arguments.hpp"

int
main(int argc, char **argv)
{
	(void)argv;

	if (check_argc_number(argc))
		return 1;

	std::cout << "Web server C++98" << std::endl;

	Config *config = Json::read("config.json");

	config->print_all();

	delete config;

	return 0;
}
