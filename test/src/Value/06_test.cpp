#include "Value.hpp"

int test_output(json::Value const &, std::string const &);

int
test_value_object_array(void)
{
	json::t_object *main_object;
	json::t_object *json_object;
	json::t_array  *json_array;

	main_object = new json::t_object;
	json_object = new json::t_object;

	json_array = new json::t_array;

	json_object->insert(std::make_pair("width", json::Value(new double(12))));
	json_object->insert(std::make_pair("heigth", json::Value(new double(42))));
	json_object->insert(std::make_pair("name", json::Value(new std::string("rectangle"))));
	json_object->insert(std::make_pair("true", json::Value(new bool(true))));

	json_array->push_back(json::Value(new std::string("zero")));
	json_array->push_back(json::Value(new std::string("one")));
	json_array->push_back(json::Value(new std::string("two")));

	main_object->insert(std::make_pair("object", json::Value(json_object)));
	main_object->insert(std::make_pair("array", json::Value(json_array)));

	json::Value config(main_object);

	if (config.get("object").get("width").get<double>() != 12)
		return 1;

	if (config.get("object").get("heigth").get<double>() != 42)
		return 1;

	if (config.get("object").get("name").get<std::string>() != "rectangle")
		return 1;

	if (config.get("object").get("true").get<bool>() != true)
		return 1;

	if (config.get("array")[0].get<std::string>() != "zero")
		return 1;

	if (config.get("array")[1].get<std::string>() != "one")
		return 1;

	if (config.get("array")[2].get<std::string>() != "two")
		return 1;

	if (test_output(config, "{\"array\" : [\"zero\", \"one\", \"two\"], \"object\" : {\"heigth\" : 42, "
							"\"name\" : \"rectangle\", \"true\" : true, \"width\" : 12}}\n"))
		return 1;

	return 0;
}
