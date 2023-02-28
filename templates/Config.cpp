template <typename T>
T
Config::get(std::string const &key)
{
	std::map<std::string, Value>::iterator it(_config.find(key));
	if (it == _config.end())
		throw std::runtime_error("Config: do not find pair with \"" + key + "\" as key");
	return it->second.get<T>();
}
