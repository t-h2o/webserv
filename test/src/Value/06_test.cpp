#include "Value.hpp"

int
test_value_object_array(void)
{
	Value::t_object *main_object;
	Value::t_object *json_object;
	Value::t_array	*json_array;

	main_object = new Value::t_object;
	json_object = new Value::t_object;

	json_array = new Value::t_array;

	json_object->insert(std::make_pair("width", Value(new double(12))));
	json_object->insert(std::make_pair("heigth", Value(new double(42))));
	json_object->insert(std::make_pair("name", Value(new std::string("rectangle"))));
	json_object->insert(std::make_pair("true", Value(new bool(true))));

	json_array->push_back(Value(new std::string("zero")));
	json_array->push_back(Value(new std::string("one")));
	json_array->push_back(Value(new std::string("two")));

	main_object->insert(std::make_pair("object", Value(json_object)));
	main_object->insert(std::make_pair("array", Value(json_array)));

	Value config(main_object);

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

	return 0;
}
