#include "Config.hpp"

int
test_config_insert(void)
{
	Config config;

	config.insert_pair(std::make_pair("key1", Value(new std::string("value1"))));
	config.insert_pair(std::make_pair("key2", Value(new std::string("value2"))));
	config.insert_pair(std::make_pair("key3", Value(new double(42))));
	config.insert_pair(std::make_pair("key4", Value(new double(1234.5678))));

	{
		Config config_copy(config);
	}

	{
		Config config_copy = config;
	}

	return 0;
}
