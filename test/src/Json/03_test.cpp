#include "Stream.hpp"

#include "Config.hpp"
#include "Json.hpp"

static int
test_empty_string(const char *path)
{
	Config *config;

	config = read(path);
	if (config)
		return 1;
	return 0;
}

int
test_json_empty_string(void)
{
	if (test_empty_string("test/src/Json/config_empty_string00.json"))
		return 1;
	if (test_empty_string("test/src/Json/config_empty_string01.json"))
		return 1;
	return 0;
}
