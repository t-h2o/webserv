#include "Config.hpp"

void
Config::insert_pair(t_pair const &pair)
{
	_config.insert(pair);
}

void
Config::_print_pair(t_pair pair)
{
	std::cout << pair.first << " : " << pair.second << std::endl;
}

void
Config::print_all(void) const
{
	for_each(_config.begin(), _config.end(), _print_pair);
}
