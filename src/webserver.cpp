#include <iostream>

int
webserver(const char *path)
{
	(void)path;

	std::cout << "Web server written in C++98" << std::endl;

	Config config;
	config.insert_pair(std::make_pair("key", new Value("value")));
	config.print_all();

	return 0;
}
