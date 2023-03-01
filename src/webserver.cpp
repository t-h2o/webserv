#include <iostream>
#include "Config.hpp"

int
webserver(const char *path)
{
	(void)path;

	std::cout << "Web server written in C++98" << std::endl;

	return 0;
}
