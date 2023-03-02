#include "Stream.hpp"

#include "Config.hpp"
#include "Json.hpp"

static int
test_config(Config *config)
{
	Stream output;

	output.open();
	config->print_all();
	output.close();

	if (output.check("age : 42\n", ""))
		return 1;

	return 0;
}

int
test_json_number(void)
{
	Stream	output;
	Config *config;

	output.open();
	config = read("test/src/Json/config_number.json");
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
