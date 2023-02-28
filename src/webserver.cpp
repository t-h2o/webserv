#include <iostream>

int
webserver(const char *path)
{
	(void)path;

	std::cout << "Web server C++98" << std::endl;

	Config config;
	config.insert_pair(std::make_pair("key", new Value("value")));
	config.insert_pair(std::make_pair("asdf", new Value(42)));
	std::cout << " number asdf: " << config.get<double>("asdf") << std::endl;
	config.print_all();

	return 0;
}
