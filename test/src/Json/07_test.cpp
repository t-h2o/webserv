#include "Stream.hpp"

#include "Config.hpp"
#include "Json.hpp"

int
test_json_array_number(void)
{
	Stream	output;
	Config *config;

	output.open();
	config = read("test/src/Json/config_array_number00.json");
	output.close();

	delete config;

	return 0;
}
