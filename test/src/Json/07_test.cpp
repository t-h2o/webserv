#include "Stream.hpp"

#include "Json.hpp"

int
test_json_array_number(void)
{
	Stream			 output;
	Value::t_object *config;

	output.open();
	config = read("test/src/Json/config_array_number00.json");
	output.close();

	delete config;

	return 0;
}
