#include "Json.hpp"
#include "serverTest.hpp"

#include <iostream>

int
webserver(const char *path_config_file)
{
	std::cout << "Web server written in C++98" << std::endl;

	json::t_object *config(0);

	if (json::load_config(path_config_file, &config))
		return 1;

	std::cout << *config << std::endl;

	delete config;

	return 0;
}
