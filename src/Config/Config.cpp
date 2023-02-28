#include "Config.hpp"

Config::~Config(void) { _free_values(); }

void
Config::insert_pair(t_pair const &pair)
{
	_config.insert(pair);
}

void
Config::_print_pair(t_pair pair)
{
	std::cout << pair.first << " : " << *(pair.second) << std::endl;
}

double
Config::get(std::string const &key)
{
	std::map<std::string, Value *>::iterator it(_config.find(key));
	if (it == _config.end())
		throw std::exception();
	return it->second->get<double>();
}

void
Config::print_all(void) const
{
	for_each(_config.begin(), _config.end(), _print_pair);
}

void
Config::_delete_value(t_pair pair)
{
	delete pair.second;
}

void
Config::_free_values(void)
{
	for_each(_config.begin(), _config.end(), _delete_value);
}
