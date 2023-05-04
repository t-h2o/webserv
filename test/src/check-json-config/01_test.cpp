#include "Stream.hpp"
#include "utils_json.hpp"

int
test_json_check_config_normal(void)
{
	json::t_object *config;

	config = new json::t_object;

	(*config)["port"] = json::Value(new double(80));
	(*config)["path"] = json::Value(new std::string("/path"));

	if (json::check_config(config))
	{
		delete config;
		return 1;
	}

	delete config;
	return 0;
}
