#include "Value.hpp"

int
test_value_map_value(void)
{
	std::map<std::string, Value> *config;
	std::map<std::string, Value> *object;

	config = new std::map<std::string, Value>;
	object = new std::map<std::string, Value>;

	config->insert(std::make_pair("key1", Value(new std::string("value1"))));
	object->insert(std::make_pair("key2", Value(new std::string("value2"))));
	config->insert(std::make_pair("object", Value(object)));

	delete config;

	return 0;
}
