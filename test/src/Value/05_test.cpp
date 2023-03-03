#include "Value.hpp"

int
test_value_map_value(void)
{
	Value::t_object *config;
	Value::t_object *object;

	config = new Value::t_object;
	object = new Value::t_object;

	config->insert(std::make_pair("key1", Value(new std::string("value1"))));
	object->insert(std::make_pair("key2", Value(new std::string("value2"))));
	config->insert(std::make_pair("object", Value(object)));

	Value val(config);

	val.get<std::string>("key1");

	return 0;
}
