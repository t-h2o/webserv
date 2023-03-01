#include "Config.hpp"

int
test_config_get(void)
{
	Config config;

	config.insert_pair(std::make_pair("key1", Value("value1")));
	config.insert_pair(std::make_pair("key2", Value("value2")));
	config.insert_pair(std::make_pair("key3", Value(42)));
	config.insert_pair(std::make_pair("key4", Value(1234.5678)));

	if (config.get<std::string>("key1") != "value1")
		return 1;
	if (config.get<std::string>("key2") != "value2")
		return 1;
	if (config.get<double>("key3") != 42)
		return 1;
	if (config.get<double>("key4") != 1234.5678)
		return 1;
	{
		Config config_copy(config);

		if (config_copy.get<std::string>("key1") != "value1")
			return 1;
		if (config_copy.get<std::string>("key2") != "value2")
			return 1;
		if (config_copy.get<double>("key3") != 42)
			return 1;
		if (config_copy.get<double>("key4") != 1234.5678)
			return 1;
	}

	{
		Config config_copy = config;

		if (config_copy.get<std::string>("key1") != "value1")
			return 1;
		if (config_copy.get<std::string>("key2") != "value2")
			return 1;
		if (config_copy.get<double>("key3") != 42)
			return 1;
		if (config_copy.get<double>("key4") != 1234.5678)
			return 1;
	}

	return 0;
}
