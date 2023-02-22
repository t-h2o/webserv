#include "Config.hpp"
#include "Json.hpp"

void
webserver(char const *path)
{
	Config *config = Json::read(path);

	config->print_all();

	delete config;
}
