#include "Value.hpp"

int
test_value_no_existing_key(void)
{
	json::t_object *main_object;

	main_object = new json::t_object;

	main_object->insert(std::make_pair("key", json::Value(new double(12))));

	json::Value config(main_object);

	if (config.get("key").get<double>() != 12)
		return 1;

	config.get("no-existing-key").get<std::string>();

	return 0;
}
