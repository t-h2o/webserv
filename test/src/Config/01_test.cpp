#include "Config.hpp"

int
test_config_insert(void)
{
	Config config;

	config.insert_pair(std::make_pair("key1", Value("value1")));
	config.insert_pair(std::make_pair("key2", Value("value2")));

	return 0;
}
