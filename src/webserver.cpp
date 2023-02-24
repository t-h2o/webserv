#include "Config.hpp"
#include "Json.hpp"

int
webserver(char const *path)
{
	Config *config(0);

	try
	{
		config = Json::read(path);
	}
	catch (const std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	if (config == 0)
		return 1;

	config->print_all();

	delete config;

	return 0;
}
