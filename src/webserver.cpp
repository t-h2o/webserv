#include "serverTest.hpp"
#include <iostream>

int
webserver(const char *path)
{
	(void)path;

	std::cout << "Web server written in C++98" << std::endl;
	serverTest();

	return 0;
}
