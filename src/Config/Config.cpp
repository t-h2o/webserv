#include "Config.hpp"

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
