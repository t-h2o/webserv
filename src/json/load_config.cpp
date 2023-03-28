#include "utils_json.hpp"
#include <iostream>

namespace json
{

int
load_config(const char *path_config_file, t_object **config)
{
	try
	{
		*config = read(path_config_file);
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	if (*config == 0)
		return 1;

	return 0;
}

} /* namespace json */
