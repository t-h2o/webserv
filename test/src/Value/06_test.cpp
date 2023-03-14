#include "Value.hpp"

int test_output(Json::Value const &, std::string const &);

int
test_value_object_array(void)
{
	Json::Value::t_object *main_object;
	Json::Value::t_object *json_object;
	Json::Value::t_array  *json_array;

	main_object = new Json::Value::t_object;
	json_object = new Json::Value::t_object;

	json_array = new Json::Value::t_array;

	json_object->insert(std::make_pair("width", Json::Value(new double(12))));
	json_object->insert(std::make_pair("heigth", Json::Value(new double(42))));
	json_object->insert(std::make_pair("name", Json::Value(new std::string("rectangle"))));
	json_object->insert(std::make_pair("true", Json::Value(new bool(true))));

	json_array->push_back(Json::Value(new std::string("zero")));
	json_array->push_back(Json::Value(new std::string("one")));
	json_array->push_back(Json::Value(new std::string("two")));

	main_object->insert(std::make_pair("object", Json::Value(json_object)));
	main_object->insert(std::make_pair("array", Json::Value(json_array)));

	Json::Value config(main_object);

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
