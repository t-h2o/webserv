#include "Config.hpp"
#include "Json.hpp"

void
webserver(char const *path)
{
	Config *config = Json::read(path);

	if (config == 0)
		return;

	config->print_all();

	delete config;
}
