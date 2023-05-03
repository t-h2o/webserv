#include "utils_json.hpp"
#include <iostream>

namespace json
{

static int
check_value_path(t_object *config)
{
	if (config->find("path") != config->end())
	{
		std::cerr << "Error: not path in the config" << std::endl;
		return 1;
	}
	if (config->at("path").get_type() != JSON_STRING)
	{
		std::cerr << "Error: the path is not a string" << std::endl;
		return 1;
	}
	return 0;
}

static int
check_value_port(t_object *config)
{
	if (config->find("port") != config->end())
	{
		std::cerr << "Error: not port in the config" << std::endl;
		return 1;
	}
	if (config->at("port").get_type() != JSON_NUMBER)
	{
		std::cerr << "Error: the port is not a number" << std::endl;
		return 1;
	}
	double port(config->at("port").get<double>());
	if (port < 0 || 65000 < port)
	{
		std::cerr << "Error: port over-range" << std::endl;
		return 1;
	}
	return 0;
}

int
check_config(t_object *config)
{
	if (check_value_path(config))
		return 1;
	if (check_value_port(config))
		return 1;

	return 0;
}

} /* namespace json */
