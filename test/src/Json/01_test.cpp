#include "Config.hpp"
#include "Json.hpp"

int
test_json_normal_file(void)
{
	Config *config = Json::read("test/src/Json/config.json");

	if (config == 0)
		return 1;

	delete config;

	return 0;
}
