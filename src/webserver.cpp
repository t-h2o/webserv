#include "Config.hpp"
#include "Json.hpp"

int
webserver(char const *path)
{
	Config *config(0);

	try
	{
		config = read(path);
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	if (config == 0)
		return 1;

	config->print_all();

	delete config;

	return 0;
}
