#include <iostream>

int
webserver(const char *path)
{
	(void)path;

	std::cout << "Web server C++98" << std::endl;

	Config config;
	config.insert_pair(std::make_pair("key", Value("value")));
	config.insert_pair(std::make_pair("asdf", Value(42)));
	std::cout << " number asdf: " << config.get<double>("asdf") << std::endl;
	try
	{
		std::cout << " number asdf: " << config.get<double>("nodefine") << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
	config.print_all();

	return 0;
}
