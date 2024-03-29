#include "Value.hpp"

int test_output(json::Value const &, std::string const &);

int
test_value_map_value(void)
{
	json::t_object *config;
	json::t_object *object;

	config = new json::t_object;
	object = new json::t_object;

	config->insert(std::make_pair("key1", json::Value(new std::string("value1"))));
	object->insert(std::make_pair("key2", json::Value(new std::string("value2"))));
	config->insert(std::make_pair("object", json::Value(object)));

	json::Value val(config);

	if (val.get("key1").get<std::string>() != "value1")
		return 1;

	if (val.get("object").get("key2").get<std::string>() != "value2")
		return 1;

	if (test_output(val, "{\"key1\" : \"value1\", \"object\" : {\"key2\" : \"value2\"}}\n"))
		return 1;

	return 0;
}
