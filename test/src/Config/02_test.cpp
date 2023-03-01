#include "Config.hpp"

int
test_config_get(void)
{
	Config config;

	config.insert_pair(std::make_pair("key1", Value("value1")));
	config.insert_pair(std::make_pair("key2", Value("value2")));

	if (config.get<std::string>("key1") != "value1")
		return 1;
	if (config.get<std::string>("key2") != "value2")
		return 1;
	{
		Config config_copy(config);

		if (config_copy.get<std::string>("key1") != "value1")
			return 1;
		if (config_copy.get<std::string>("key2") != "value2")
			return 1;
	}

	{
		Config config_copy = config;

		if (config_copy.get<std::string>("key1") != "value1")
			return 1;
		if (config_copy.get<std::string>("key2") != "value2")
			return 1;
	}

	return 0;
}
