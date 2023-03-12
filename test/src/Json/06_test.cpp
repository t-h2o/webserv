#include "Stream.hpp"

#include "Json.hpp"

static int
test_config(Value::t_object *config)
{
	Stream output;

	output.open();
	std::cout << *config << std::endl;
	output.close();

	if (output.check("{\"age\" : 42, \"firstName\" : \"John\"}\n", ""))
		return 1;

	return 0;
}

int
test_json_string_number(void)
{
	Stream			 output;
	Value::t_object *config;

	output.open();
	config = read("test/src/Json/config_string_number.json");
	output.close();

	if (config == 0)
		return 1;

	if (output.check("", ""))
		return 1;

	if (test_config(config))
	{
		delete config;
		return 1;
	}

	delete config;

	return 0;
}
