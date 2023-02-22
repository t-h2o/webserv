#include "Config.hpp"
#include "Json.hpp"

int
webserver(char const *path)
{
	Config *config = Json::read(path);

	if (config == 0)
		return 1;

	config->print_all();

	delete config;

	return 0;
}
