#include "Value.hpp"

int test_output(Json::Value const &, std::string const &);

int
test_value_map_value(void)
{
	Json::t_object *config;
	Json::t_object *object;

	config = new Json::t_object;
	object = new Json::t_object;

	config->insert(std::make_pair("key1", Json::Value(new std::string("value1"))));
	object->insert(std::make_pair("key2", Json::Value(new std::string("value2"))));
	config->insert(std::make_pair("object", Json::Value(object)));

	Json::Value val(config);

	if (val.get("key1").get<std::string>() != "value1")
		return 1;

	if (val.get("object").get("key2").get<std::string>() != "value2")
		return 1;

	if (test_output(val, "{\"key1\" : \"value1\", \"object\" : {\"key2\" : \"value2\"}}\n"))
		return 1;

	return 0;
}
