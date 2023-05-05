#include "Stream.hpp"
#include "utils_json.hpp"

int
test_json_check_config_bad_port(void)
{
	json::t_object *config;

	// the port shouldn't be a string
	{
		config = new json::t_object;

		(*config)["port"] = json::Value(new std::string("I'm not a number"));
		(*config)["path"] = json::Value(new std::string("/path"));

		if (json::check_config(config) == 0)
		{
			delete config;
			return 1;
		}

		delete config;
		return 0;
	}

	// the port should exist
	{
		config = new json::t_object;

		(*config)["path"] = json::Value(new std::string("/path"));

		if (json::check_config(config) == 0)
		{
			delete config;
			return 1;
		}

		delete config;
		return 0;
	}
}
