#include "Json.hpp"

int
webserver(char const *path)
{
	Value::t_object *config(0);

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

	std::cout << *config << std::endl;

	delete config;

	return 0;
}
