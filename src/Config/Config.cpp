#include "Config.hpp"

Config::~Config(void) { _free_values(); }

void
Config::insert_key(std::string const &key)
{
	t_pair node(key, 0);

	_config.insert(node);
	_last_key = key;
}

void
Config::insert_value(Value *value)
{
	std::map<std::string, Value *>::iterator it = _config.find(_last_key);
	it->second = value;
}

void
Config::_print_pair(t_pair pair)
{
	std::cout << pair.first << " : " << *(pair.second) << std::endl;
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
