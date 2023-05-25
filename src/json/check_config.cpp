#include "utils_json.hpp"
#include <climits>
#include <iostream>
#include <unistd.h>

#define DEFAULT_SERVER_NAME "default_server_name"

namespace json
{

static int
check_value_servername(t_object &config)
{
	if (config.find("server_name") == config.end())
	{
		config["server_name"] = json::Value(new std::string(DEFAULT_SERVER_NAME));
		return 0;
	}
	else if (config.at("server_name").get_type() != JSON_STRING)
	{
		std::cerr << "Error: the server_name is not a string" << std::endl;
		return 1;
	}
	return 0;
}

static int
check_value_path(t_object const &config)
{
	if (config.find("path") == config.end())
	{
		std::cerr << "Error: not path in the config" << std::endl;
		return 1;
	}
	if (config.at("path").get_type() != JSON_STRING)
	{
		std::cerr << "Error: the path is not a string" << std::endl;
		return 1;
	}
	return 0;
}

static int
check_cgi(t_object const *config)
{
	if (config->find("php-cgi") == config->end())
	{
		std::cerr << "Error: not \"php-cgi\" path in the config" << std::endl;
		return 1;
	}
	if (config->at("php-cgi").get_type() != JSON_STRING)
	{
		std::cerr << "Error: the php-cgi is not a string" << std::endl;
		return 1;
	}
	if (access(config->at("php-cgi").get<std::string>().c_str(), X_OK))
	{
		std::cerr << "Error: the php-cgi can't be execute" << std::endl;
		return 1;
	}
	return 0;
}

static int
check_value_port(t_object const &config)
{
	if (config.find("port") == config.end())
	{
		std::cerr << "Error: not port in the config" << std::endl;
		return 1;
	}
	if (config.at("port").get_type() != JSON_NUMBER)
	{
		std::cerr << "Error: the port is not a number" << std::endl;
		return 1;
	}
	double port(config.at("port").get<double>());
	if (port < 0 || USHRT_MAX < port)
	{
		std::cerr << "Error: port over-range" << std::endl;
		return 1;
	}
	return 0;
}

static int
check_server_config(t_object &config)
{
	if (check_value_path(config))
		return 1;
	if (check_value_port(config))
		return 1;
	if (check_value_servername(config))
		return 1;
	return 0;
}

/* check the content of the configuration file
 */
int
check_config(t_object *config)
{
	for (t_object::iterator server_config(config->begin()); server_config != config->end(); ++server_config)
	{
		if (server_config->second.get_type() == JSON_OBJECT)
		{
			if (check_server_config(server_config->second.get<t_object>()))
				return 1;
		}
	}

	if (check_cgi(config))
		return 1;

	return 0;
}

} /* namespace json */
