#include "Config.hpp"

int
test_config_insert(void)
{
	Config config;

	config.insert_pair(std::make_pair("key1", Value("value1")));
	config.insert_pair(std::make_pair("key2", Value("value2")));
	config.insert_pair(std::make_pair("key3", Value(42)));
	config.insert_pair(std::make_pair("key4", Value(1234.5678)));

	{
		Config config_copy(config);
	}

	{
		Config config_copy = config;
	}

	return 0;
}
